#include "pch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLGraphicsAPI.h"

namespace Ramensoup
{
	GraphicsAPI* Renderer::s_GraphicsAPI = nullptr;
	Renderer::API Renderer::s_API = API::None;

	Renderer::SceneContext Renderer::s_SceneContext;
	Renderer::Statistics Renderer::s_Statistics;

	void Renderer::Init(API api)
	{
		s_API = api;

		if (s_GraphicsAPI)
			delete s_GraphicsAPI;

		switch (api)
		{
		case API::OpenGL:
			s_GraphicsAPI = new OpenGLGraphicsAPI();
			s_GraphicsAPI->Init();
			break;
		case API::None:
			RS_CORE_ASSERT(false, "Renderer::API::None is not supported.");
		}
	}
	void Renderer::BeginScene(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
	{
		s_SceneContext.ViewProjectionMatrix = projectionMatrix * viewMatrix;
		s_SceneContext.CameraPosition = glm::inverse(viewMatrix)[3];
		s_SceneContext.LightSourceCount = 0;
		ResetStatistics();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform)
	{
		auto& vertexBuffer = mesh->GetVertexBuffer();
		auto& indexBuffer = mesh->GetIndexBuffer();

		material->Bind();

		material->SetMat4Value("u_ModelMatrix", transform);
		material->SetMat4Value("u_ViewProjectionMatrix", s_SceneContext.ViewProjectionMatrix);

		for (int lightId = 0; lightId < s_SceneContext.LightSourceCount; lightId++)
		{
			std::ostringstream oss;
			oss << "u_LightSources[" << lightId << "]";
			material->SetFloat3Value(oss.str() + ".Position", s_SceneContext.LightSources[lightId].Position);
			material->SetFloat3Value(oss.str() + ".Color", s_SceneContext.LightSources[lightId].Color * s_SceneContext.LightSources[lightId].Intensity);
			material->SetFloat3Value(oss.str() + ".Attenuation", s_SceneContext.LightSources[lightId].Attenuation);
		}

		material->SetIntValue("u_LightCount", s_SceneContext.LightSourceCount);
		material->SetFloat3Value("u_AmbientLight", {0.2,0.2,0.2});

		material->SetFloat1Value("u_MaterialParams.Ka", 0);
		material->SetFloat1Value("u_MaterialParams.Kd", 0.5f);
		material->SetFloat1Value("u_MaterialParams.Ks", 0.5f);
		material->SetFloat1Value("u_MaterialParams.Shineness", 32);

		material->SetFloat3Value("u_CameraPosition", s_SceneContext.CameraPosition);

		DrawIndexed(vertexBuffer, indexBuffer, indexBuffer->GetCount());

	}

	void Renderer::SubmitLightSource(const glm::vec3& position, const glm::vec3& color, const glm::vec3& attenuation, float intensity)
	{
		// Need some kind of guard for too many lights
		uint32_t lightId = s_SceneContext.LightSourceCount++;
		s_SceneContext.LightSources[lightId].Position = position;
		s_SceneContext.LightSources[lightId].Intensity = intensity;
		s_SceneContext.LightSources[lightId].Color = color;
		s_SceneContext.LightSources[lightId].Attenuation = attenuation;
	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, size_t indexCount)
	{
		s_GraphicsAPI->DrawIndexed(vertexBuffer, indexBuffer, indexCount);
		
		s_Statistics.DrawCallCount++;
		s_Statistics.TotalIndexCount += indexCount;
	}

	void Renderer::ResetStatistics()
	{
		s_Statistics.DrawCallCount = 0;
		s_Statistics.TotalIndexCount = 0;
	}
}