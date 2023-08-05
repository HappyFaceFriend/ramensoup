#include <pch.h>
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLGraphicsAPI.h"

namespace Ramensoup
{
	GraphicsAPI* Renderer::s_GraphicsAPI = nullptr;
	Renderer::API Renderer::s_API = API::None;

	Renderer::SceneContext Renderer::s_SceneContext;

	void Renderer::Init(API api)
	{
		s_API = api;

		if (s_GraphicsAPI)
			delete s_GraphicsAPI;

		switch (api)
		{
		case API::OpenGL:
			s_GraphicsAPI = new OpenGLGraphicsAPI();
			break;
		case API::None:
			RS_CORE_ASSERT(false, "Renderer::API::None is not supported.");
		}
	}
	void Renderer::BeginScene(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
	{
		s_SceneContext.ViewProjectionMatrix = projectionMatrix * viewMatrix;
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material, const glm::mat4& transform)
	{
		auto& vertexBuffer = mesh->GetVertexBuffer();
		auto& indexBuffer = mesh->GetIndexBuffer();

		material->GetShader()->Bind();
		material->GetShader()->SetUniformMat4("u_ModelMatrix", transform);
		material->GetShader()->SetUniformMat4("u_ViewProjectionMatrix", s_SceneContext.ViewProjectionMatrix);

		DrawIndexed(vertexBuffer, indexBuffer, indexBuffer->GetCount());

	}

	void Renderer::DrawIndexed(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, uint32_t indexCount)
	{
		s_GraphicsAPI->DrawIndexed(vertexBuffer, indexBuffer, indexCount);
	}
}