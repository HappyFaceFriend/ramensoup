#include <pch.h>
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Ramensoup
{

	const std::shared_ptr<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::OpenGL:
			return std::shared_ptr<Shader>(new OpenGLShader(filePath));
		}
		RS_CORE_ASSERT(false, "Unknwon RendererAPI");
		return nullptr;
	}
	const std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//TODO : implement this
		RS_CORE_ASSERT(false, "NOT IMPLEMENTED");
		return nullptr;
	}
}