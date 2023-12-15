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


	void Scene::UpdateHierarchyTransforms()
	{
		//https://skypjack.github.io/2019-08-20-ecs-baf-part-4-insights/

		m_Registry.sort<RelationshipComponent>([&](const entt::entity lhs, const entt::entity rhs)
			{
				const auto& clhs = m_Registry.get<RelationshipComponent>(lhs);
				const auto& crhs = m_Registry.get<RelationshipComponent>(rhs);
				return crhs.GetParent().GetID() == lhs || clhs.GetNextSibling().GetID() == rhs
					|| (!(clhs.GetParent().GetID() == rhs || crhs.GetNextSibling().GetID() == lhs)
						&& (clhs.GetParent().GetID() < crhs.GetParent().GetID() 
							|| (clhs.GetParent().GetID() == crhs.GetParent().GetID() && &clhs < &crhs)));
			});

		auto view = m_Registry.view<TransformComponent, RelationshipComponent>();
		for (auto entity : view)
		{
			auto& [transform, relationship] = view.get<TransformComponent, RelationshipComponent>(entity);
			if (relationship.GetParent())
				transform.ParentModelMatrix = relationship.GetParent().GetComponent<TransformComponent>().GetMatrix();
		}
	}
	void Scene::RenderMeshes(const Camera& camera)
	{
		Renderer::BeginScene(camera.GetProjectionMatrix(), camera.GetViewMatrix());
		
		auto view = m_Registry.view<TransformComponent, MeshRendererComponent>();
		for (auto entity : view)
		{
			auto& [transform, meshRenderer] = view.get<TransformComponent, MeshRendererComponent>(entity);
			Renderer::Submit(meshRenderer.Mesh, meshRenderer.Material, transform.GetMatrix());
		}
		Renderer::EndScene();
	}
}