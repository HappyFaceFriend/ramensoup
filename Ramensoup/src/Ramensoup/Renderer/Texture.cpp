#include <pch.h>
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Ramensoup
{
	std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::OpenGL:
			return std::shared_ptr<Texture2D>(new OpenGLTexture2D(width, height));
		}
		RS_CORE_ASSERT(false, "Unknwon RendererAPI");
		return nullptr;
	}
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::OpenGL:
			return std::shared_ptr<Texture2D>(new OpenGLTexture2D(path));
		}
		RS_CORE_ASSERT(false, "Unknwon RendererAPI");
		return nullptr;
	}
}