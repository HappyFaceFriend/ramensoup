#include <pch.h>
#include "VertexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Ramensoup
{
	const std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float* verticies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::OpenGL:
			return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(verticies, size));
		}
		RS_CORE_ASSERT(false, "Unknwon RendererAPI");
		return nullptr;
	}
}