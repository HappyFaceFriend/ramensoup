#include <pch.h>
#include "PerspectiveCameracontroller.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

namespace Ramensoup
{
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio, float yFov, float zNear, float zFar)
		:m_AspectRatio(aspectRatio), m_YFieldOfView(yFov), m_Near(zNear), m_Far(zFar)
	{
		m_Camera.SetPerspective(yFov, aspectRatio, zNear, zFar);
	}
	void PerspectiveCameraController::OnUpdate()
	{
		float speed = m_TranslationSpeed;
		if (Input::IsMouseButtonPressed(1))
		{
			glm::vec3 right = glm::cross(m_Up, m_Front);
			if (Input::IsKeyPressed(RS_KEY_A))
				m_Position -= right * speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_D))
				m_Position += right * speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_W))
				m_Position += m_Front * speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_S))
				m_Position -= m_Front * speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_E))
				m_Position += m_Up * speed * Time::GetDeltaTime();
			if (Input::IsKeyPressed(RS_KEY_Q))
				m_Position -= m_Up * speed * Time::GetDeltaTime();

			if (m_LastMousePos.x != -1)
			{
				float xRot = (Input::GetMousePos().y - m_LastMousePos.y) * m_RotationSpeed;
				float yRot = (Input::GetMousePos().x - m_LastMousePos.x) * m_RotationSpeed;

				m_Front = glm::rotate(glm::mat4(1.0f), xRot, right) * glm::rotate(glm::mat4(1.0f), yRot, m_Up) * glm::vec4(m_Front, 0);
				m_Up = glm::rotate(glm::mat4(1.0f), yRot, m_Up) * glm::vec4(m_Up, 0);
			}
			m_LastMousePos = Input::GetMousePos();
		}
		else
		{
			m_LastMousePos = { -1, -1 };
		}

		m_Camera.SetView(glm::lookAt(m_Position, m_Position + m_Front, m_Up));
	}
	void PerspectiveCameraController::OnViewportResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetPerspective(m_YFieldOfView, m_AspectRatio, m_Near, m_Far);
	}
}