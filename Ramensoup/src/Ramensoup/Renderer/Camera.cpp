#pragma once
#include "pch.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Ramensoup
{
	Camera::Camera()
		:m_ProjectionMatrix(1.0f), m_ViewMatrix(1.0f)
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::SetOrthographic(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
	}
	void Camera::SetOrthographic(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
	}
	void Camera::SetPerspective(float yFov, float aspectRatio, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(yFov, aspectRatio, zNear, zFar);
	}
}