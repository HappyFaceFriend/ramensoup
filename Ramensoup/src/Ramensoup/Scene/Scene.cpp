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
		// https://skypjack.github.io/2019-08-20-ecs-baf-part-4-insights/
		// TODO : Sort only the dirty transforms (mark dirty when parent is changed)
		// TODO : This sorts lasty by address, so mabye mark the creation or hierarchy order

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
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		auto& camera = m_Registry.get<CameraComponent>(GetMainCamera());
		camera.Projection.SetViewportSize(width, height);
	}
	void Scene::Clear()
	{
		auto view = m_Registry.view<TransformComponent>();
		for (auto entity : view)
		{
			m_Registry.destroy(entity);
		}
	}
	entt::entity Scene::GetMainCamera() const
	{
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (entt::entity entity : view)
		{
			return entity;
		}
		return entt::null;
	}
	void Scene::RenderMeshes()
	{
		glm::mat4 projectionMatrix, viewMatrix;
		auto& [transform, camera] = m_Registry.get<TransformComponent, CameraComponent>(GetMainCamera());

		projectionMatrix = camera.Projection.GetProjectionMatrix();
		viewMatrix = glm::inverse(transform.GetMatrix());

		Renderer::BeginScene(projectionMatrix, viewMatrix);

		auto view = m_Registry.view<TransformComponent, MeshRendererComponent>();
		for (auto entity : view)
		{
			auto& [transform, meshRenderer] = view.get<TransformComponent, MeshRendererComponent>(entity);
			Renderer::Submit(meshRenderer.Mesh, meshRenderer.Material, transform.GetMatrix());
		}
		Renderer::EndScene();
	}
}