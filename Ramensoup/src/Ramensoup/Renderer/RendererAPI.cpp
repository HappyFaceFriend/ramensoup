#include <pch.h>
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ramensoup
{
	GraphicsAPI RendererAPI::s_API = GraphicsAPI::OpenGL;

}