#pragma once

#include "Entity.h"

#include <Ramensoup/Utils/zstring_view.h>

#include <glm/glm.hpp>

#include <string>

namespace Ramensoup
{
	struct TagComponent
	{
		std::string Tag{""};

		TagComponent() = default;
		TagComponent(const zstring_view& tag)
			:Tag(tag) {}
	};

	//To change hierarchy, use Entity::SetParent()
	struct RelationshipComponent
	{
	public:
		[[nodiscard]] const Entity& GetParent() const noexcept { return m_Parent; }
		[[nodiscard]] const Entity& GetFirstChild() const noexcept { return m_FirstChild; }
		[[nodiscard]] const Entity& GetLastChild() const noexcept { return m_LastChild; }
		[[nodiscard]] const Entity& GetPrevSibling() const noexcept { return m_PrevSibling; }
		[[nodiscard]] const Entity& GetNextSibling() const noexcept { return m_NextSibling; }
	private:
		Entity m_Parent;
		Entity m_FirstChild;
		Entity m_LastChild;
		Entity m_PrevSibling;
		Entity m_NextSibling;

		friend Entity;
	};

	struct TransformComponent
	{
		glm::vec3 Position{0.0f, 0.0f, 0.0f};
		glm::vec3 Rotation{0.0f, 0.0f, 0.0f};
		glm::vec3 Scale{0.0f, 0.0f, 0.0f};

		TransformComponent() = default;
	};
}