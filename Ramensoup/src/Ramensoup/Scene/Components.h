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
		const Entity& GetParent() const noexcept { return m_Parent; }
		const Entity& GetFirstChild() const noexcept { return m_FirstChild; }
		const Entity& GetLastChild() const noexcept { return m_LastChild; }
		const Entity& GetPrevSibling() const noexcept { return m_PrevSibling; }
		const Entity& GetNextSibling() const noexcept { return m_NextSibling; }
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
		glm::mat4 Matrix{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const glm::mat4& matrix)
			:Matrix(matrix) {}
	};
}