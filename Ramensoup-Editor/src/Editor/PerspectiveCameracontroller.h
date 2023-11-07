#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, float yFov, float zNear, float zFar);
		~PerspectiveCameraController();

		void OnUpdate();

		inline const Camera& GetCamera() const { return m_Camera; }
	private:
		Camera m_Camera;
		float m_AspectRatio;
		float m_YFieldOfView;
		float m_Near;
		float m_Far;

		glm::vec3 m_Position{0, 0, 10};
		glm::vec3 m_Rotation{0, 0, 0};

		float m_TranslationSpeed = 1;
		float m_RotationSpeed = 0.7f;
	};
}