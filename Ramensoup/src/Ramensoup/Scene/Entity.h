#pragma once

#include "Scene.h"

#include <entt.hpp>

namespace Ramensoup
{
	//Entity is just a wrapper with helper functions of entt::entity (an ID)
	class Entity
	{
	public:
		[[nodiscard]] Entity() = default;
		[[nodiscard]] Entity(entt::entity handle, Scene* scene) noexcept;

		[[nodiscard]] operator bool() const noexcept { return m_ID != entt::null; }
		[[nodiscard]] bool operator==(const Entity& other) const noexcept { return m_ID == other.m_ID; }
		[[nodiscard]] bool operator!=(const Entity& other) const noexcept { return m_ID != other.m_ID; }

		void SetParent(Entity parentEntity);

		[[nodiscard]] bool IsNull() const noexcept { return m_ID == entt::null; }

		[[nodiscard]] entt::entity GetID() const noexcept { return m_ID; }

		template<typename T>
		[[nodiscard]] bool HasComponent() const
		{
			return m_Scene->m_Registry.all_of<T>(m_ID);
		}

		template<typename T>
		[[nodiscard]] T& GetComponent() const
		{
			RS_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
			return m_Scene->m_Registry.get<T>(m_ID);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			RS_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_ID, std::forward<Args>(args)...);
		}

		template<typename T>
		T& RemoveComponent()
		{
			RS_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
			return m_Scene->m_Registry.remove<T>(m_ID);
		}

	private:
		entt::entity m_ID{ entt::null };
		Scene* m_Scene = nullptr;
	};
}