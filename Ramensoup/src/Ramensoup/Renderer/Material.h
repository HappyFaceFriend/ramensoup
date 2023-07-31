#pragma once

#include "Shader.h"

namespace Ramensoup
{


	class Material
	{
	public:
		Material(const char * name, const std::shared_ptr<Shader>& shader);
		~Material();

		inline std::shared_ptr<Shader> GetShader() const { return m_Shader; }
	private:
		std::string m_Name;
		std::shared_ptr<Shader> m_Shader;

	};
}