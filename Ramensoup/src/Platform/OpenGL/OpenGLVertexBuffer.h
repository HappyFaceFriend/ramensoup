#pragma once

#include "Ramensoup/Renderer/VertexBuffer.h"

namespace Ramensoup
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		[[nodiscard]] OpenGLVertexBuffer(uint32_t size);
		[[nodiscard]] OpenGLVertexBuffer(const void* data, size_t size);
		~OpenGLVertexBuffer() override;

		OpenGLVertexBuffer(const OpenGLVertexBuffer&) = delete;
		OpenGLVertexBuffer(OpenGLVertexBuffer&&) = delete;
		OpenGLVertexBuffer& operator=(const OpenGLVertexBuffer&) = delete;
		OpenGLVertexBuffer& operator=(OpenGLVertexBuffer&&) = delete;

		void Bind() const override;
		void Unbind() const override;

		void SetData(const void* data, uint32_t size) override;

		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		[[nodiscard]] const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}