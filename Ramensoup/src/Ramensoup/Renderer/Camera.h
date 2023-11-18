#pragma once

#include <glm/glm.hpp>

namespace Ramensoup
{
	class Camera
	{
	public:
		Camera() = default;

		void SetOrthographic(float left, float right, float bottom, float top);
		void SetOrthographic(float left, float right, float bottom, float top, float zNear, float zFar);
		void SetPerspective(float yFov, float aspectRatio, float zNear, float zFar);

		inline void SetTransform(const glm::mat4& transform) { m_ViewMatrix = glm::inverse(transform); }
		inline void SetView(const glm::mat4& view) { m_ViewMatrix = view; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

	private:
		//TODO : Cache View / Projection matricies & Change m_Transform to transform component
		glm::mat4 m_ProjectionMatrix{ 1.0f };
		//glm::mat4 m_Transform;
		glm::mat4 m_ViewMatrix{ 1.0f };
		
	};

	//TODO : Change this to just Rect
	struct OrthoGraphicCameraBounds
	{
		float Left, Right, Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};
}