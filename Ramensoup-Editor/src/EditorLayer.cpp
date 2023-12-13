#include "EditorLayer.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace Ramensoup
{
	EditorLayer::EditorLayer()
		:m_CameraController(16.0f / 9.0f, glm::radians(60.0f), 0.1f, 100), m_ViewportSize(0, 0),
		m_Scene(std::make_shared<Scene>()), m_SceneHierarchyPanel(m_Scene)
	{
		m_ModelTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	}
	void EditorLayer::OnAttach()
	{
		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbSpec);

		//m_Meshes = MeshLoader::LoadOBJ("assets/models/Toyota Supra MK4 Custom/model/mk5_on_4.obj");
		m_Meshes = MeshLoader::LoadOBJ("assets/models/low-poly-garen_/source/b137609479e34bc3bf215142d91b745b.obj");
		m_Shader = Shader::Create("assets/shaders/Lit.glsl");

		m_Material = std::shared_ptr<Material>(new Material("Lit", m_Shader));
		m_Material->GetShader()->Bind();
		//m_Material->GetShader()->SetUniformFloat4("u_Color", glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));

		m_Texture = Texture2D::Create("assets/models/low-poly-garen_/textures/garen_tex.jpg");
		m_Texture->Bind();
		Renderer::SetClearColor(glm::vec4(0.2, 0.2, 0.2, 1));

		auto entity1 = m_Scene->CreateEntity("Entity1");
		auto entity2c1 = m_Scene->CreateEntity("Entity2 - c1");
		auto entity2p = m_Scene->CreateEntity("Entity2 - p");
		auto entity2c2 = m_Scene->CreateEntity("Entity2 - c2");
		auto entity2c2c = m_Scene->CreateEntity("Entity2 - c2 - c");

		entity2c1.SetParent(entity2p);
		entity2c2.SetParent(entity2p);
		entity2c2c.SetParent(entity2c2);
	}
	void EditorLayer::OnDetach() noexcept
	{
		RS_LOG("OnDetach");
	}
	void EditorLayer::OnUpdate()
	{
		m_CameraController.OnUpdate();

		TimeProfiler::Begin("Single Frame Render");
		m_FrameBuffer->Bind();
		Renderer::Clear();
		Renderer::BeginScene(m_CameraController.GetCamera().GetProjectionMatrix(), m_CameraController.GetCamera().GetViewMatrix());

		for (auto mesh : m_Meshes)
			Renderer::Submit(mesh, m_Material, m_ModelTransform);
		Renderer::EndScene();
		m_FrameBuffer->Unbind();
		TimeProfiler::End("Single Frame Render");
	}
	void EditorLayer::OnImGuiUpdate()
	{
		ImGuiCommands::EnableDockspace();

		//Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");
		m_ViewportFocused = ImGui::IsWindowFocused();
		Application::Get().GetImGuiLayer().SetBlockEvents(!m_ViewportFocused);
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_CameraController.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

		ImGui::PopStyleVar();
		ImGui::End();

		TimeProfiler::Begin("Editor GUI Render");
		//Scene Hierarchy Panel
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
		ImGui::Begin("test window2");
		glm::vec3 position = m_CameraController.GetPosition();
		ImGui::DragFloat3("Camera Position", glm::value_ptr(position));
		ImGui::End();
	}

}


