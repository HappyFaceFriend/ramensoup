#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: Implement multiple light types. Currently point light
struct LightSourceComponent
{
	glm::vec3 Color {1, 1, 1};
	glm::vec3 Attenuation {1, 0, 0};
	float Intensity {1};

	LightSourceComponent() = default;
};