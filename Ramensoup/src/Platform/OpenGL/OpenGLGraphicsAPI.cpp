#include <pch.h>
#include "OpenGLGraphicsAPI.h"

#include <glad/glad.h>

namespace Ramensoup
{
	void OpenGLGraphicsAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	void OpenGLGraphicsAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLGraphicsAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLGraphicsAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	std::shared_ptr<OpenGLVertexArray>& OpenGLGraphicsAPI::AllocateVertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		std::shared_ptr<OpenGLVertexArray> vertexArray = std::shared_ptr<OpenGLVertexArray>(new OpenGLVertexArray());
		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);
		m_VertexArrayMap[vertexBuffer.get()] = vertexArray;
		return vertexArray;
	}
	void OpenGLGraphicsAPI::DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, uint32_t indexCount)
	{
		std::shared_ptr<OpenGLVertexArray> vertexArray;
		if (m_VertexArrayMap.find(vertexBuffer.get()) == m_VertexArrayMap.end())
		{
			vertexArray = AllocateVertexArray(vertexBuffer, indexBuffer);
		}
		else
		{
			vertexArray = m_VertexArrayMap[vertexBuffer.get()];
			if (vertexArray->GetIndexBuffer() != indexBuffer)
				vertexArray->SetIndexBuffer(indexBuffer);
		}
		DrawIndexed(vertexArray, indexCount);
	}

	void OpenGLGraphicsAPI::DrawIndexed(const std::shared_ptr<OpenGLVertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		vertexArray->Bind();
		vertexArray->GetIndexBuffer()->Bind();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}