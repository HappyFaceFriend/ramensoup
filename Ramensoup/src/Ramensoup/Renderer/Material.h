#pragma once

#include "Shader.h"

namespace Ramensoup
{


	class Material
	{
	public:
		Material(const std::string_view& name, const std::shared_ptr<Shader>& shader);

		inline std::shared_ptr<Shader> GetShader() const { return m_Shader; }
	private:
		std::string m_Name;
		std::shared_ptr<Shader> m_Shader;
	};
}