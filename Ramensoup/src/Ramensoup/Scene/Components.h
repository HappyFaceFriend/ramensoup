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
	struct TransformComponent
	{
		glm::mat4 Matrix{ 1.0f };
	private:
		Entity m_Parent;
		std::vector<Entity> m_Children;

	public:
		TransformComponent() = default;
		TransformComponent(const glm::mat4& matrix)
			:Matrix(matrix) {}

		const Entity& GetParent() const noexcept { return m_Parent; }
		const std::vector<Entity>& GetChildren() const noexcept { return m_Children;  }
		friend Entity;
	};
}