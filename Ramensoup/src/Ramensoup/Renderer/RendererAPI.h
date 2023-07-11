#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Ramensoup
{
	enum class GraphicsAPI
	{
		None = 0, OpenGL = 1
	};
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;
		virtual void Init() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, uint32_t indexCount = 0) = 0;

		static inline GraphicsAPI GetAPI() { return s_API; }

	private:
		static GraphicsAPI s_API;
	};
}