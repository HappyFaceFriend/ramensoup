#pragma once

#include "GraphicsAPI.h"

namespace Ramensoup
{
	class Renderer
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

	public:
		static void Init(API api);

		static void BeginScene(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		static void EndScene();

		static void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, uint32_t indexCount = 0);


		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_GraphicsAPI->SetViewport(x, y, width, height);
		}
		inline static void Clear()
		{
			s_GraphicsAPI->Clear();
		}
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_GraphicsAPI->SetClearColor(color);
		}
		inline static API GetAPI() { return s_API; }

	private:
		struct SceneContext
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneContext m_SceneContext;

		static GraphicsAPI* s_GraphicsAPI;
		static API s_API;
	};
}