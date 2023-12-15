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


		DrawIndexed(vertexBuffer, indexBuffer, indexBuffer->GetCount());

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