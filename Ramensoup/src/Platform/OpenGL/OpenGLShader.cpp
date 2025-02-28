#include "pch.h"
#include "OpenGLShader.h"

namespace Ramensoup
{
	static GLenum ShaderTypeFromString(const std::string_view& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		RS_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

	static std::string GetFileName(const zstring_view& filePath)
	{
		auto lastSlash = filePath.find_last_of("/\\");
		if (lastSlash == std::string::npos)
			lastSlash = 0;
		else
			lastSlash += 1;

		auto lastDot = filePath.rfind('.');
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		return std::string(filePath.substr(lastSlash, count));
	}
	
	OpenGLShader::OpenGLShader(const zstring_view& filePath)
	{
		std::string source = ReadFile(filePath);
		m_Name = GetFileName(filePath);

		auto shaderSources = PreProcess(source);
		Compile(shaderSources);
		InitUniformLocations(source);

	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}
	void OpenGLShader::InitUniformLocations(const std::string& source)
	{
		uint8_t textureSlot = 0;
		auto uniformToken = "uniform";
		size_t pos = source.find(uniformToken, 0);
		while (pos != std::string::npos)
		{
			size_t semicolon = source.find_first_of(";", pos);
			size_t nameStart = source.rfind(' ', semicolon) + 1;
			size_t typeStart = source.rfind(' ', nameStart - 2) + 1;
			std::string typeName = source.substr(typeStart, nameStart - typeStart - 1);
			std::string uniformName = source.substr(nameStart, semicolon - nameStart);
			RS_CORE_LOG_INFO("Shader {1} has: {2} {0}", uniformName, m_Name, typeName);
			m_UniformLocations[uniformName] = glGetUniformLocation(m_RendererID, uniformName.c_str());
			if (typeName == "sampler2D")
				m_TextureSlots[uniformName] = textureSlot++;

			pos = source.find(uniformToken, semicolon);
		}
		
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();
		RS_CORE_ASSERT(shaderSources.size() <= 3, "Too many shaders to compile");

		std::array<GLenum, 3> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = (const GLchar*)source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				RS_CORE_LOG_ERROR("{0}", infoLog.data());
				RS_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (int i = 0; i < glShaderIDIndex; i++)
				glDeleteShader(glShaderIDs[i]);

			// Use the infoLog as you see fit.
			RS_CORE_LOG_ERROR("{0}", infoLog.data());
			RS_CORE_ASSERT(false, "Shader linking failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (int i = 0; i < glShaderIDIndex; i++)
			glDetachShader(m_RendererID, glShaderIDs[i]);

		m_RendererID = program;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			RS_CORE_ASSERT(eol != std::string::npos, "Syntax error");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			RS_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);

			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

		}
		return shaderSources;
	}
	std::string OpenGLShader::ReadFile(const zstring_view& filePath)
	{
		std::string result;
		std::ifstream in(filePath.data(), std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			//RS_CORE_LOG_ERROR("Could not open shader {0}", filePath);
		}
		return result;
	}
	
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	// TODO: Uniform functions need to be cleaned. Can't call map.find every time parameter is set.

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(m_UniformLocations[name], 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& values)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(m_UniformLocations[name], values.x, values.y, values.z, values.w);
	}
	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& values)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(m_UniformLocations[name], values.x, values.y, values.z);
	}
	void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& values)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(m_UniformLocations[name], values.x, values.y);
	}
	void OpenGLShader::SetUniformFloat1(const std::string& name, float value)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(m_UniformLocations[name], value);
	}
	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(m_UniformLocations[name], value);
	}
	void OpenGLShader::SetUniformIntArray(const std::string& name, int* values, int count)
	{
		if (m_UniformLocations.find(name) == m_UniformLocations.end())
			m_UniformLocations[name] = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(m_UniformLocations[name], count, values);
	}
	void OpenGLShader::SetTexture(const std::string& name, const std::shared_ptr<Texture2D>& texture)
	{
		texture->Bind(m_TextureSlots[name]);
	}
}
