#include <pch.h>
#include "PerspectiveCameracontroller.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Ramensoup
{
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float yFov, float zNear, float zFar)
		:m_AspectRatio(aspectRatio), m_YFieldOfView(yFov), m_Near(zNear), m_Far(zFar)
	{
		m_Camera.SetPerspective(yFov, aspectRatio, zNear, zFar);
	}
	PerspectiveCameraController::~PerspectiveCameraController()
	{
	}
	void PerspectiveCameraController::OnUpdate()
	{
		float speed = m_TranslationSpeed;
		if (!Input::IsMouseButtonPressed(1))
		{
			if (Input::IsKeyPressed(RS_KEY_A))
				m_Position.x -= speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_D))
				m_Position.x += speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_W))
				m_Position.z += speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_S))
				m_Position.z -= speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_E))
				m_Position.y += speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_Q))
				m_Position.y -= speed * Time::GetDeltaTime();
		}
		else
		{
			if (Input::IsKeyPressed(RS_KEY_A))
				m_Rotation.y += m_RotationSpeed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_D))
				m_Rotation.y -= m_RotationSpeed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_W))
				m_Rotation.x += m_RotationSpeed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_S))
				m_Rotation.x -= m_RotationSpeed * Time::GetDeltaTime();
		}

		m_Camera.SetTransform(glm::translate(glm::mat4(1.0f), m_Position)
			* glm::rotate(glm::mat4(1.0f), m_Rotation.x, glm::vec3(1,0,0))
			* glm::rotate(glm::mat4(1.0f), m_Rotation.y, glm::vec3(0,1 ,0)));
	}
}