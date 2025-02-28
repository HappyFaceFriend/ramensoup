#pragma once

#include "GraphicsAPI.h"
#include "Mesh.h"
#include "Material.h"

namespace Ramensoup
{
	class Renderer
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
		//TODO : Debug & Release only
		struct Statistics
		{
			uint32_t DrawCallCount = 0;
			size_t TotalIndexCount = 0;
		};

		constexpr static uint32_t MaxLightSourceCount = 8;

	public:
		Renderer() = delete;

	public:
		static void Init(API api);

		static void BeginScene(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

		static void Submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform = glm::mat4(1.0f));
		static void SubmitLightSource(const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation, float intensity);
		static void EndScene();

		static void DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, size_t indexCount = 0);


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

		inline static const Statistics& GetStatistics() { return s_Statistics; }

	private:
		static void ResetStatistics();

	private:
		struct LightSourceData
		{
			glm::vec3 Position;
			glm::vec3 Color;
			glm::vec3 Attenuation;
			float Intensity;
		};
		struct SceneContext
		{
			glm::mat4 ViewProjectionMatrix;
			glm::vec3 CameraPosition;
			LightSourceData LightSources[MaxLightSourceCount];
			uint32_t LightSourceCount;
		} static s_SceneContext;

		static Statistics s_Statistics;

		static GraphicsAPI* s_GraphicsAPI;
		static API s_API;
	};
}