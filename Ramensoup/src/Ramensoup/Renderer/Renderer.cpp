#include <pch.h>
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLGraphicsAPI.h"

namespace Ramensoup
{
	GraphicsAPI* Renderer::s_GraphicsAPI;
	Renderer::API Renderer::s_API = API::None;

	void Renderer::Init(API api)
	{
		s_API = api;

		switch (api)
		{
		case API::OpenGL:
			s_GraphicsAPI = new OpenGLGraphicsAPI();
			break;
		case API::None:
			RS_CORE_ASSERT(false, "Renderer::API::None is not supported.");
		}
	}
}