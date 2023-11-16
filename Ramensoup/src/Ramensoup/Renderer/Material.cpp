#include "pch.h"
#include "Material.h"

namespace Ramensoup
{

	Material::Material(const char * name, const std::shared_ptr<Shader>& shader)
		:m_Name(name), m_Shader(shader)
	{
	}
	Material::~Material()
	{
	}
}