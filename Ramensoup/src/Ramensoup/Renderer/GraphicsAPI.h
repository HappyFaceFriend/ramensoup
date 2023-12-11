#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>

namespace Ramensoup
{
	class GraphicsAPI
	{
		friend class Renderer;
	public:
		[[nodiscard]] virtual ~GraphicsAPI() = default;
		GraphicsAPI(const GraphicsAPI&) = delete;
		GraphicsAPI(GraphicsAPI&&) = delete;
		GraphicsAPI& operator=(const GraphicsAPI&) = delete;
		GraphicsAPI& operator=(GraphicsAPI&&) = delete;

	protected:
		[[nodiscard]] GraphicsAPI() = default;

		virtual void Init() = 0;

		virtual void Clear() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, size_t indexCount = 0) = 0;

	};
}