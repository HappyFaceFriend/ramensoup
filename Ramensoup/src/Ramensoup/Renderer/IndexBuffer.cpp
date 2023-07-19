#include <pch.h>
#include "IndexBuffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Ramensoup
{

	const std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indicies, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::OpenGL:
			return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indicies, count));
		}
		RS_CORE_ASSERT(false, "Unknwon RendererAPI");
		return nullptr;
	}
}