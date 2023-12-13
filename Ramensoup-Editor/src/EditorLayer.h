#pragma once

#include <Ramensoup.h>

#include "Editor/PerspectiveCameraController.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/InspectorPanel.h"

namespace Ramensoup
{
	class EditorApp;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() noexcept override;
		virtual void OnUpdate() override;
		virtual void OnImGuiUpdate() override;
	private:

		std::shared_ptr<Shader> m_Shader;

		std::vector<std::shared_ptr<Mesh>> m_Meshes;
		std::shared_ptr<Material> m_Material;
		std::shared_ptr<Texture2D> m_Texture;
		glm::mat4 m_ModelTransform = glm::mat4(1.0f);

		std::shared_ptr<FrameBuffer> m_FrameBuffer;

		bool m_ViewportFocused = false;
		glm::vec2 m_ViewportSize{0, 0};

		PerspectiveCameraController m_CameraController;

		std::shared_ptr<Scene> m_Scene;

		SceneHierarchyPanel m_SceneHierarchyPanel;
		InspectorPanel m_InspectorPanel;
	};
}