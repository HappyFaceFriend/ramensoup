#include "pch.h"
#include "Entity.h"

#include "Components.h"

namespace Ramensoup
{
	Entity::Entity(entt::entity id, Scene* scene) noexcept
		:m_ID(id), m_Scene(scene)
	{
	}

	void Entity::SetParent(const Entity& parent)
	{
		parent.GetComponent<TransformComponent>().m_Children.push_back(*this);
		GetComponent<TransformComponent>().m_Parent = parent;;
	}
}