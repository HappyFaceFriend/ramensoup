#pragma once

#include "Ramensoup/Renderer/Camera.h"

#include <entt.hpp>

namespace Ramensoup
{
	class Entity;
	class SceneHierarchyPanel;

	class Scene
	{
	public:
		Scene() = default;

		Entity CreateEntity(const zstring_view& name = "New Entity");

		void RenderMeshes(const Camera& camera);
	private:
		entt::registry m_Registry;

		friend Entity;
		friend SceneHierarchyPanel;
	};
}