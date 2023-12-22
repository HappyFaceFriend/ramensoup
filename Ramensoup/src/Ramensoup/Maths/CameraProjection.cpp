#include "pch.h"
#include "CameraProjection.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ramensoup 
{
	void CameraProjection::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		m_ProjectionType = Type::Perspective;
		m_PerspectiveFOV = verticalFOV;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		UpdatePerspectiveProjection();
	}

	void CameraProjection::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = Type::Orthographic;
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		UpdateOrthographicProjection();
	}

	void CameraProjection::SetViewportSize(uint32_t width, uint32_t height)
	{
		RS_CORE_ASSERT(width > 0 && height > 0, "Invalid viewport size");
		m_AspectRatio = (float)width / (float)height;
		if (m_ProjectionType == Type::Perspective)
			UpdatePerspectiveProjection();
		else
			UpdateOrthographicProjection();
	}

	void CameraProjection::SetProjectionType(Type type)
	{
		m_ProjectionType = type;

		if (m_ProjectionType == Type::Perspective)
			UpdatePerspectiveProjection();
		else
			UpdateOrthographicProjection();
	}

	void CameraProjection::UpdatePerspectiveProjection()
	{
		m_ProjectionMatrix = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
	}

	void CameraProjection::UpdateOrthographicProjection()
	{
		float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
		float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
		float orthoBottom = -m_OrthographicSize * 0.5f;
		float orthoTop = m_OrthographicSize * 0.5f;

		m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight,
			orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar);
	}
}