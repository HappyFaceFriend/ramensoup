#pragma once

#include <glm/glm.hpp>

#include <string>
#include <Ramensoup/Utils/zstring_view.h>

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

		TransformComponent() = default;
		TransformComponent(const glm::mat4& matrix)
			:Matrix(matrix) {}
	};
}