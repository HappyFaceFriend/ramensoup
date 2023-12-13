#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, float ySize);

		void OnUpdate(); 
		void OnViewportResize(float width, float height);

		inline const Camera& GetCamera() const { return m_Camera; }
	private:
		Camera m_Camera;
		float m_AspectRatio;
		float m_YSize;
		OrthoGraphicCameraBounds m_Bounds;

		glm::vec3 m_Position{0, 0, 0};
		float m_Rotation = 0;

		float m_TranslationSpeed = 1;
		float m_RotationSpeed = 90;
	};
}