#include <pch.h>
#include "OrthographicCameraController.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Ramensoup
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, float ySize)
		:m_AspectRatio(aspectRatio), m_YSize(ySize), m_Bounds({ -aspectRatio * ySize, aspectRatio * ySize, -ySize, ySize })
	{
		m_Camera.SetOrthographic(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}
	void OrthographicCameraController::OnUpdate()
	{
		float speed = m_TranslationSpeed;
		if (Input::IsKeyPressed(RS_KEY_A))
			m_Position.x -= speed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(RS_KEY_D))
			m_Position.x += speed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(RS_KEY_W))
			m_Position.y += speed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(RS_KEY_S))
			m_Position.y -= speed * Time::GetDeltaTime();


		float rotationSpeed = m_RotationSpeed;
		if (Input::IsKeyPressed(RS_KEY_Q))
			m_Rotation += rotationSpeed * Time::GetDeltaTime();
		if (Input::IsKeyPressed(RS_KEY_E))
			m_Rotation -= rotationSpeed * Time::GetDeltaTime();

		m_Camera.SetTransform(glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)));
	}
	void OrthographicCameraController::OnViewportResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Bounds.Left = -m_AspectRatio * m_YSize;
		m_Bounds.Right = m_AspectRatio * m_YSize;
		m_Camera.SetOrthographic(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}
}