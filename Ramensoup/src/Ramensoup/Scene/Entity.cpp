#include "pch.h"
#include "Entity.h"

#include "Components.h"

namespace Ramensoup
{
	Entity::Entity(entt::entity id, Scene* scene) noexcept
		:m_ID(id), m_Scene(scene)
	{
	}

	void Entity::SetParent(Entity parentEntity)
	{
		auto& relationship = GetComponent<RelationshipComponent>();
		relationship.m_Parent = parentEntity;

		auto& parentRelationship = parentEntity.GetComponent<RelationshipComponent>();
		if (parentRelationship.m_LastChild)
		{
			parentRelationship.m_LastChild.GetComponent<RelationshipComponent>().m_NextSibling = *this;
			relationship.m_PrevSibling = parentRelationship.m_LastChild;
			parentRelationship.m_LastChild = *this;
		}
		else
		{
			parentRelationship.m_FirstChild = *this;
			parentRelationship.m_LastChild = *this;
		}
	}
}