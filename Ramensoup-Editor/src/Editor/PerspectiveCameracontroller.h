#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, float yFov, float zNear, float zFar);

		void OnUpdate();
		void OnViewportResize(float width, float height);
		inline const Camera& GetCamera() const { return m_Camera; }
		inline const glm::vec3& GetPosition() { return m_Position; }
	private:
		Camera m_Camera;
		float m_AspectRatio;
		float m_YFieldOfView;
		float m_Near;
		float m_Far;

		glm::vec3 m_Position{0, 0, -5};
		glm::vec3 m_Front{0, 0, 1};
		glm::vec3 m_Up{0, 1, 0};

		float m_TranslationSpeed = 3;
		float m_RotationSpeed = 0.5f / 180;

		glm::vec2 m_LastMousePos = { -1, -1 };
	};
}