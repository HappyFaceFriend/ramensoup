#pragma once

#include <entt.hpp>

namespace Ramensoup
{
	class Entity;

	class Scene
	{
	public:
		Scene() = default;

		Entity CreateEntity(const zstring_view& name = "New Entity");

		void OnUpdate();
	private:
		entt::registry m_Registry;

		friend Entity;
	};
}