#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Ramensoup
{
	struct TransformComponent
	{
		glm::vec3 Position{0.0f, 0.0f, 0.0f};
		glm::vec3 Rotation{0.0f, 0.0f, 0.0f}; //In radians
		glm::vec3 Scale{1.0f, 1.0f, 1.0f};

		glm::mat4 ParentModelMatrix {1.0f};
		TransformComponent() = default;
		// TODO : Cache matrix and use isDirty to recalculate
		glm::mat4 GetMatrix() const
		{
			return ParentModelMatrix * glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(glm::quat(Rotation)) * glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}