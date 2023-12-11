#include "pch.h"
#include "FrameBuffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Ramensoup
{

	std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::API::OpenGL:
			return std::make_shared<OpenGLFrameBuffer>(spec);
		}
		RS_CORE_ASSERT(false, "Unknonw RendererAPI");
		return nullptr;
	}
}