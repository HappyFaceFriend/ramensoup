#pragma once

#include <glm/glm.hpp>

namespace Ramensoup {

	class CameraProjection
	{
	public:
		enum class Type { Perspective = 0, Orthographic = 1 };

		void SetPerspective(float verticalFOV, float nearClip, float farClip);
		void SetOrthographic(float size, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

		[[nodiscard]] Type GetProjectionType() const noexcept { return m_ProjectionType; }
		void SetProjectionType(Type type);

		[[nodiscard]] const glm::mat4 GetProjectionMatrix() const noexcept { return m_ProjectionMatrix; }

		[[nodiscard]] float GetPerspectiveVerticalFOV() const noexcept { return m_PerspectiveFOV; }
		[[nodiscard]] float GetPerspectiveNearClip() const noexcept { return m_PerspectiveNear; }
		[[nodiscard]] float GetPerspectiveFarClip() const noexcept { return m_PerspectiveFar; }
		void SetPerspectiveVerticalFOV(float verticalFov) { m_PerspectiveFOV = verticalFov; UpdatePerspectiveProjection(); }
		void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; UpdatePerspectiveProjection(); }
		void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; UpdatePerspectiveProjection(); }

		[[nodiscard]] float GetOrthographicSize() const noexcept { return m_OrthographicSize; }
		[[nodiscard]] float GetOrthographicNearClip() const noexcept { return m_OrthographicNear; }
		[[nodiscard]] float GetOrthographicFarClip() const noexcept { return m_OrthographicFar; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; UpdateOrthographicProjection(); }
		void SetOrthographicNearClip(float nearClip) { m_OrthographicNear = nearClip; UpdateOrthographicProjection(); }
		void SetOrthographicFarClip(float farClip) { m_OrthographicFar = farClip; UpdateOrthographicProjection(); }

	private:
		Type m_ProjectionType = Type::Orthographic;

		float m_PerspectiveFOV = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_AspectRatio = 0.0f;

		glm::mat4 m_ProjectionMatrix{1.0f};

	private:
		void UpdatePerspectiveProjection();
		void UpdateOrthographicProjection();
	};

}