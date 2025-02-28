#include "EditorLayer.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Meshes/Primitives/PrimitiveMeshFactory.h"

#include "Ramensoup/Scene/SceneSerializer.h"

namespace Ramensoup
{
	EditorLayer::EditorLayer()
		: m_Scene(std::make_shared<Scene>()),
		m_SceneHierarchyPanel(m_Scene), m_SceneViewPanel(m_Scene), m_GameViewPanel(m_Scene)
	{
	}
	void EditorLayer::OnAttach()
	{
		//m_Meshes = MeshLoader::LoadOBJ("assets/models/Toyota Supra MK4 Custom/model/mk5_on_4.obj");
		m_Mesh = MeshLoader::LoadOBJ("assets/models/low-poly-garen_/source/b137609479e34bc3bf215142d91b745b.obj");
		m_Shader = Shader::Create("assets/shaders/OldLit.glsl");

		m_Material = std::shared_ptr<Material>(new Material("OldLit", m_Shader));
		m_Material->SetTexture("u_DiffuseTexture", Texture2D::Create("assets/models/low-poly-garen_/textures/garen_tex.jpg"));
		
		Renderer::SetClearColor(glm::vec4(0.2, 0.2, 0.2, 1));

		m_GarenEntity = m_Scene->CreateEntity("Garen Model");
		m_GarenEntity.GetComponent<TransformComponent>().Position = glm::vec3(-10, 0, 0);
		auto& meshRenderer = m_GarenEntity.AddComponent<MeshRendererComponent>();
		meshRenderer.Mesh = m_Mesh;
		meshRenderer.Material = m_Material;

		m_Camera = m_Scene->CreateEntity("Main Camera");
		m_Camera.AddComponent<CameraComponent>();
		m_Camera.GetComponent<TransformComponent>().Position = glm::vec3(0, 0, -5);

		// Sphere test

		m_Sphere = PrimitiveMeshFactory::Create(PrimitiveMeshType::Sphere);
		m_LitShader = Shader::Create("assets/shaders/Lit.glsl");
		m_SphereMaterial = std::make_shared<Material>("Sphere Lit", m_LitShader);
		m_SphereEntity = m_Scene->CreateEntity("Sphere");
		auto& sphereMeshRenderer = m_SphereEntity.AddComponent<MeshRendererComponent>();
		sphereMeshRenderer.Mesh = m_Sphere;
		sphereMeshRenderer.Material = m_SphereMaterial;
		
		{
			m_PointLight1 = m_Scene->CreateEntity("Point Light 1");
			auto& lightSourceComponent = m_PointLight1.AddComponent<LightSourceComponent>();
			m_PointLight1.GetComponent<TransformComponent>().Position = glm::vec3(3, 0, 0);
			lightSourceComponent.Color = { 1, 0.8f, 1 };
			lightSourceComponent.Intensity = 0.5f;
		}
		{
			m_PointLight2 = m_Scene->CreateEntity("Point Light 2");
			auto& lightSourceComponent = m_PointLight2.AddComponent<LightSourceComponent>();
			m_PointLight2.GetComponent<TransformComponent>().Position = glm::vec3(-3, 0, 0);
			lightSourceComponent.Color = { 0.8f, 1, 1 };
			lightSourceComponent.Intensity = 0.5f;
		}
	}
	void EditorLayer::OnDetach() noexcept
	{
		RS_LOG("OnDetach");
	}
	void EditorLayer::OnUpdate()
	{
		TimeProfiler::Begin("Transform updates");
		m_Scene->UpdateHierarchyTransforms();
		TimeProfiler::End("Transform updates");

		m_SceneViewPanel.OnUpdate();
		m_SceneViewPanel.RenderScene();

		m_GameViewPanel.OnUpdate();
	}
	static void ImGuiBeginDockspace();

	void EditorLayer::OnImGuiUpdate()
	{
		ImGuiBeginDockspace();
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.

				if (ImGui::MenuItem("Serialize"))
				{
					SceneSerializer serializer(m_Scene);
					serializer.SerializeToText("assets/scenes/Example.rsscene");
				}
				if (ImGui::MenuItem("Deserialize"))
				{
					m_Scene->Clear();
					m_SceneHierarchyPanel.UnselectEntity();
					SceneSerializer serializer(m_Scene);
					serializer.DeserializeFromText("assets/scenes/Example.rsscene");
				}

				if (ImGui::MenuItem("Exit"))
					Application::Get().Close();
				//ImGui::Separator();

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::End();

		//Panels
		TimeProfiler::Begin("Editor GUI Render");

		m_SceneViewPanel.OnImGuiRender();

		m_GameViewPanel.OnImGuiRender();

		m_SceneHierarchyPanel.OnImGuiRender();

		m_InspectorPanel.SetEntity(m_SceneHierarchyPanel.GetSelectedEntity());
		m_InspectorPanel.OnImGuiRender();

		TimeProfiler::End("Editor GUI Render");

		//Test windows
		ImGui::Begin("test window");

		//TEMP
		static int frames = 0;
		static float deltaTimeSum = 0;
		static float lastDeltaTime = 0;
		if (frames == 1000)
		{
			frames = 0;
			lastDeltaTime = deltaTimeSum;
			deltaTimeSum = 0;
			RS_LOG("1000 frame time : {0}", lastDeltaTime);
		}
		else
		{
			deltaTimeSum += Time::GetDeltaTime();
			frames++;
		}
		ImGui::Text("Frame time (*1000): %fms", lastDeltaTime);
		ImGui::Text("FPS: %f", 1 / Time::GetDeltaTime());
		ImGui::Spacing();
		ImGui::Text("Draw Calls: %d", Renderer::GetStatistics().DrawCallCount);
		ImGui::Text("Indicies: %d", Renderer::GetStatistics().TotalIndexCount);
		ImGui::End();
	}

	static void ImGuiBeginDockspace()
	{
		static bool dockSpaceOpen = true;

		//From imgui_demo.cpp ShowExampleAppDockSpace
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

	}
}


