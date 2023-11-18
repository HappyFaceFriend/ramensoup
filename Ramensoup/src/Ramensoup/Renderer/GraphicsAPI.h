#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Ramensoup
{

	class GraphicsAPI
	{
		friend class Renderer;
	public:
		virtual ~GraphicsAPI() = default;
		GraphicsAPI(const GraphicsAPI&) = delete;
		GraphicsAPI(GraphicsAPI&&) = delete;
		GraphicsAPI& operator=(const GraphicsAPI&) = delete;
		GraphicsAPI& operator=(GraphicsAPI&&) = delete;

	protected:
		GraphicsAPI() = default;
		virtual void Init() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, uint32_t indexCount = 0) = 0;

	};
}