#pragma once

#include "Ramensoup/Renderer/GraphicsAPI.h"
#include "OpenGLVertexArray.h"

namespace Ramensoup
{
	class OpenGLGraphicsAPI : public GraphicsAPI
	{
	public:
		OpenGLGraphicsAPI() = default;
	protected:
		virtual void Init() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, size_t indexCount = 0) override;
		void DrawIndexed(const std::shared_ptr<OpenGLVertexArray>& vertexArray, size_t indexCount = 0);
	private:
		std::shared_ptr<OpenGLVertexArray> AllocateVertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);
	private:
		//TOOD : Need some kind of mark&sweep for freeing all useless vertexArrays
		std::unordered_map<VertexBuffer*, std::shared_ptr<OpenGLVertexArray>> m_VertexArrayMap;
	};
}