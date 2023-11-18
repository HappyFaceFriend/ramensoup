#pragma once

#include "Ramensoup/Renderer/IndexBuffer.h"

namespace Ramensoup
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* verticies, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;
		OpenGLIndexBuffer(const OpenGLIndexBuffer&&) = delete;
		OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;
		OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&&) = delete;

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}