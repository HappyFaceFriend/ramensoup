#include <pch.h>
#include "IndexBuffer.h"

#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Ramensoup
{

	const std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* indicies, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL:
			return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indicies, count));
		}
	}
}