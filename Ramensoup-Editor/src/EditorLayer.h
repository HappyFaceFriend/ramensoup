#pragma once

#include <Ramensoup.h>

#include "CameraControllers/PerspectiveCameraController.h"
#include "Panels/SceneViewPanel.h"
#include "Panels/GameViewPanel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/InspectorPanel.h"

namespace Ramensoup
{
	class EditorApp;

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void OnAttach() override;
		void OnDetach() noexcept override;
		void OnUpdate() override;
		void OnImGuiUpdate() override;

	private:
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_LitShader;

		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;


		std::shared_ptr<Scene> m_Scene;

		SceneViewPanel m_SceneViewPanel;
		GameViewPanel m_GameViewPanel;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		InspectorPanel m_InspectorPanel;

		Entity m_Camera;

		Entity m_GarenEntity;
		std::vector<Entity> m_GarenParts;


		std::shared_ptr<Mesh> m_Sphere;
		Entity m_SphereEntity;
		std::shared_ptr<Material> m_SphereMaterial;

		Entity m_PointLight1;
		Entity m_PointLight2;
	};
}