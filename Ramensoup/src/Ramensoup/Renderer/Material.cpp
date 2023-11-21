#include "pch.h"
#include "Material.h"

namespace Ramensoup
{

	Material::Material(const zstring_view& name, const std::shared_ptr<Shader>& shader)
		:m_Name(name), m_Shader(shader)
	{
	}
}