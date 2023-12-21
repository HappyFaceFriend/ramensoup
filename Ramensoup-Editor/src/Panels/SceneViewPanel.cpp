#include "SceneViewPanel.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

namespace Ramensoup
{
	SceneViewPanel::SceneViewPanel(const std::shared_ptr<Scene>& scene)
		: m_CurrentScene(scene), m_ViewportSize(0, 0),
		m_CameraController(16.0f / 9.0f, glm::radians(60.0f), 0.1f, 100)
	{
		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbSpec);

	}
	void SceneViewPanel::OnUpdate()
	{
		m_CameraController.OnUpdate();
	}
	void SceneViewPanel::RenderScene()
	{
		TimeProfiler::Begin("SceneView Single Frame Render");
		m_FrameBuffer->Bind();
		Renderer::Clear();
		m_CurrentScene->RenderMeshes(m_CameraController.GetCamera());
		m_FrameBuffer->Unbind();
		TimeProfiler::End("SceneView Single Frame Render");
	}
	void SceneViewPanel::OnImGuiRender()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Scene View");
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

	}
}