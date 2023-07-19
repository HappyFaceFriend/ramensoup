#pragma once

#include "Ramensoup/Renderer/Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Ramensoup
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void SetUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& values) override;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& values) override;
		virtual void SetUniformFloat2(const std::string& name, const glm::vec2& values) override;
		virtual void SetUniformFloat1(const std::string& name, float value) override;
		virtual void SetUniformInt(const std::string& name, int value) override;
		virtual void SetUniformIntArray(const std::string& name, int* values, int count) override;

	private:
		GLint GetUniformLocation(const std::string& name);
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;

		std::unordered_map<std::string, GLint> m_UniformLocations;
	};
}