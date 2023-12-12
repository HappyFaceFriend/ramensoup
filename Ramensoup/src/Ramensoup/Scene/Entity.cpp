#include "pch.h"
#include "Entity.h"

namespace Ramensoup
{
	Entity::Entity(entt::entity id, Scene* scene) noexcept
		:m_ID(id), m_Scene(scene)
	{
	}
}