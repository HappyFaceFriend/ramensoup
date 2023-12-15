#include "pch.h"
#include "Material.h"

namespace Ramensoup
{

	Material::Material(const zstring_view& name, const std::shared_ptr<Shader>& shader)
		:m_Name(name), m_Shader(shader)
	{
	}


	void Material::Bind()
	{
		m_Shader->Bind();
		for (auto& [name, value] : m_IntUniforms)
			m_Shader->SetUniformInt(name, value);
		for (auto& [name, value] : m_FloatUniforms)
			m_Shader->SetUniformFloat1(name, value);
		for (auto& [name, value] : m_Vec2Uniforms)
			m_Shader->SetUniformFloat2(name, value);
		for (auto& [name, value] : m_Vec3Uniforms)
			m_Shader->SetUniformFloat3(name, value);
		for (auto& [name, value] : m_Vec4Uniforms)
			m_Shader->SetUniformFloat4(name, value);
		for (auto& [name, value] : m_Mat3Uniforms)
			m_Shader->SetUniformMat3(name, value);
		for (auto& [name, value] : m_Mat4Uniforms)
			m_Shader->SetUniformMat4(name, value);
		for (auto& [name, value] : m_TextureUniforms)
			m_Shader->SetTexture(name, value);
	}
}