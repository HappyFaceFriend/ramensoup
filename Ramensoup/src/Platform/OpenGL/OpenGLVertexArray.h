#pragma once

#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace Ramensoup
{
	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		OpenGLVertexArray(const OpenGLVertexArray&) = delete;
		OpenGLVertexArray(OpenGLVertexArray&&) = delete;
		OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;
		OpenGLVertexArray& operator=(OpenGLVertexArray&&) = delete;

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		//TOOD : Need some kind of mark&sweep for freeing all useless vertexArrays
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};
}