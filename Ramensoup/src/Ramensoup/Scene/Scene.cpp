#include "pch.h"
#include "Scene.h"

#include "Entity.h"
#include "Components.h"

#include "Ramensoup/Renderer/Renderer.h"

namespace Ramensoup
{
	Entity Scene::CreateEntity(const zstring_view& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<RelationshipComponent>();
		return entity;
	}


	void Scene::RenderMeshes(const Camera& camera)
	{
		Renderer::BeginScene(camera.GetProjectionMatrix(), camera.GetViewMatrix());
		
		auto view = m_Registry.view<TransformComponent, MeshRendererComponent>();
		for (auto entity : view)
		{
			auto [transform, meshRenderer] = view.get<TransformComponent, MeshRendererComponent>(entity);
			Renderer::Submit(meshRenderer.Mesh, meshRenderer.Material, transform.GetMatrix());
		}
		Renderer::EndScene();
	}
}