#pragma once

#include "CameraControllers/OrthographicCameraController.h"
#include "CameraControllers/PerspectiveCameraController.h"

#include <Ramensoup.h>

namespace Ramensoup
{
	class SceneViewPanel
	{
	public:
		SceneViewPanel(const std::shared_ptr<Scene>& scene);

		void RenderScene();

		void OnUpdate();
		void OnImGuiRender();

		void SetScene(std::shared_ptr<Scene> scene) noexcept { m_CurrentScene = scene; }
	private:
		std::shared_ptr<Scene> m_CurrentScene;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;
		bool m_ViewportFocused = false;
		glm::vec2 m_ViewportSize{0, 0};
		
		// TODO : Merge these in to one camera controller
		PerspectiveCameraController m_CameraController;
		//OrthographicCameraController m_CameraController;
	};
}