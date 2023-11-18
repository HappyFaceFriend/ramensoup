#include "pch.h"
#include "Material.h"

namespace Ramensoup
{

	Material::Material(std::string&& name, const std::shared_ptr<Shader>& shader)
		:m_Name(std::move(name)), m_Shader(shader)
	{
	}
}