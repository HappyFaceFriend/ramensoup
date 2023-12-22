#include "GameViewPanel.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

namespace Ramensoup
{
	GameViewPanel::GameViewPanel(const std::shared_ptr<Scene>& scene)
		: m_CurrentScene(scene), m_ViewportSize(0, 0)
	{
		FrameBufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_FrameBuffer = FrameBuffer::Create(fbSpec);
	}
	void GameViewPanel::OnUpdate()
	{
		RenderScene();
	}
	void GameViewPanel::RenderScene()
	{
		TimeProfiler::Begin("GameView Single Frame Render");
		m_FrameBuffer->Bind();
		Renderer::Clear();
		m_CurrentScene->RenderMeshes();
		m_FrameBuffer->Unbind();
		TimeProfiler::End("GameView Single Frame Render");
	}
	void GameViewPanel::OnImGuiRender()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Game View");
		m_ViewportFocused = ImGui::IsWindowFocused();
		Application::Get().GetImGuiLayer().SetBlockEvents(!m_ViewportFocused);
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize) && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
		{
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_FrameBuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_CurrentScene->OnViewportResize(viewportPanelSize.x, viewportPanelSize.y);
		}

		uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<ImTextureID>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

		ImGui::PopStyleVar();
		ImGui::End();

	}
}