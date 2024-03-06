#pragma once

#include "Ramensoup/Renderer/Camera.h"

#include <entt.hpp>

namespace Ramensoup
{
	class Entity;
	class SceneHierarchyPanel;
	class SceneSerializer;

	class Scene
	{
	public:
		Scene() = default;

		Entity CreateEntity(const zstring_view& name = "New Entity");

		void UpdateHierarchyTransforms();
		void RenderMeshes();
		void RenderMeshes(const Camera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		entt::registry m_Registry;

		[[nodiscard]] entt::entity GetMainCamera() const;

		friend Entity;
		friend SceneHierarchyPanel;
		friend SceneSerializer;
	};
}