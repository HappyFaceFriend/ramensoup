#pragma once

#include "Ramensoup/Renderer/Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Ramensoup
{
	class OpenGLShader : public Shader
	{
	public:
		[[nodiscard]] OpenGLShader(const zstring_view& filePath);
		~OpenGLShader() override;

		OpenGLShader(const OpenGLShader&) = delete;
		OpenGLShader(OpenGLShader&&) = delete;
		OpenGLShader& operator=(const OpenGLShader&) = delete;
		OpenGLShader& operator=(OpenGLShader&&) = delete;

		void Bind() const override;
		void Unbind() const override;
		
		[[nodiscard]] const std::string& GetName() const override { return m_Name; }

		void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		void SetUniformMat3(const std::string& name, const glm::mat3& matrix) override;
		void SetUniformFloat4(const std::string& name, const glm::vec4& values) override;
		void SetUniformFloat3(const std::string& name, const glm::vec3& values) override;
		void SetUniformFloat2(const std::string& name, const glm::vec2& values) override;
		void SetUniformFloat1(const std::string& name, float value) override;
		void SetUniformInt(const std::string& name, int value) override;
		void SetUniformIntArray(const std::string& name, int* values, int count) override;
		void SetTexture(const std::string& name, const std::shared_ptr<Texture2D>& texture) override;

	private:
		uint32_t m_RendererID;
		std::string m_Name;

		std::unordered_map<std::string, GLint> m_UniformLocations;
		std::unordered_map<std::string, uint8_t> m_TextureSlots;


	private:
		std::string ReadFile(const zstring_view& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		void InitUniformLocations(const std::string& source);
	};
}