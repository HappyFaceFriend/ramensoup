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
	OrthographicCameraController::~OrthographicCameraController()
	{
	}
	void OrthographicCameraController::OnUpdate()
	{
		float speed = m_TranslationSpeed;
		if (Input::IsKeyPressed(RS_KEY_A))
			m_Position.x -= speed;
		if (Input::IsKeyPressed(RS_KEY_D))
			m_Position.x += speed;
		if (Input::IsKeyPressed(RS_KEY_W))
			m_Position.y += speed;
		if (Input::IsKeyPressed(RS_KEY_S))
			m_Position.y -= speed;


		float rotationSpeed = m_RotationSpeed;
		if (Input::IsKeyPressed(RS_KEY_Q))
			m_Rotation += rotationSpeed;
		if (Input::IsKeyPressed(RS_KEY_E))
			m_Rotation -= rotationSpeed;

		m_Camera.SetTransform(glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)));
	}
}