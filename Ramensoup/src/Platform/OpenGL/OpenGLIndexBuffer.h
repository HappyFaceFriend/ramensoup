#pragma once

#include "Ramensoup/Renderer/IndexBuffer.h"

namespace Ramensoup
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		[[nodiscard]] OpenGLIndexBuffer(const uint32_t* verticies, size_t count);
		~OpenGLIndexBuffer() override;

		OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;
		OpenGLIndexBuffer(const OpenGLIndexBuffer&&) = delete;
		OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;
		OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&&) = delete;

		void Bind() const override;
		void Unbind() const override;
		[[nodiscard]] size_t GetCount() const override { return m_Count; }
	private:
		uint32_t m_RendererID;
		size_t m_Count;
	};
}