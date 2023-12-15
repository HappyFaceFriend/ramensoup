#pragma once
#include "Shader.h"
#include "Texture.h"

namespace Ramensoup
{
	class Material
	{
	public:
		using Texture2DType = std::shared_ptr<Texture2D>;
		[[nodiscard]] Material(const zstring_view& name, const std::shared_ptr<Shader>& shader);

		void Bind();

		inline std::shared_ptr<Shader> GetShader() const { return m_Shader; }

		// TODO : Mabye make binding optional?
		void SetMat4Value(const std::string& name, const glm::mat4& value) { m_Mat4Uniforms[name] = value; m_Shader->SetUniformMat4(name, value); }
		void SetMat3Value(const std::string& name, const glm::mat3& value) { m_Mat3Uniforms[name] = value; m_Shader->SetUniformMat3(name, value);}
		void SetFloat4Value(const std::string& name, const glm::vec4& value) { m_Vec4Uniforms[name] = value; m_Shader->SetUniformFloat4(name, value);}
		void SetFloat3Value(const std::string& name, const glm::vec3& value) { m_Vec3Uniforms[name] = value; m_Shader->SetUniformFloat3(name, value);}
		void SetFloat2Value(const std::string& name, const glm::vec2& value) { m_Vec2Uniforms[name] = value; m_Shader->SetUniformFloat2(name, value);}
		void SetFloat1Value(const std::string& name, float value) { m_FloatUniforms[name] = value;m_Shader->SetUniformFloat1(name, value); }
		void SetIntValue(const std::string& name, int value) { m_IntUniforms[name] = value; m_Shader->SetUniformInt(name, value);}
		void SetTexture(const std::string& name, const Texture2DType& texture) { m_TextureUniforms[name] = texture; m_Shader->SetTexture(name, texture);}

	private:
		std::string m_Name;
		std::shared_ptr<Shader> m_Shader;

		std::unordered_map<std::string, int> m_IntUniforms;
		std::unordered_map<std::string, float> m_FloatUniforms;
		std::unordered_map<std::string, glm::vec2> m_Vec2Uniforms;
		std::unordered_map<std::string, glm::vec3> m_Vec3Uniforms;
		std::unordered_map<std::string, glm::vec4> m_Vec4Uniforms;
		std::unordered_map<std::string, glm::mat3> m_Mat3Uniforms;
		std::unordered_map<std::string, glm::mat4> m_Mat4Uniforms;
		std::unordered_map<std::string, Texture2DType> m_TextureUniforms;
	};
}