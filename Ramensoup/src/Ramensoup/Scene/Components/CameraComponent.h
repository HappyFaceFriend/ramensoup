#pragma once

#include "Ramensoup/Maths/CameraProjection.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Ramensoup
{
	struct CameraComponent
	{
		CameraProjection Projection;
	};
}