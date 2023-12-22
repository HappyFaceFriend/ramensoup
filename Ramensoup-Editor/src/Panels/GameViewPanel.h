#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class GameViewPanel
	{
	public:
		GameViewPanel(const std::shared_ptr<Scene>& scene);

		void OnUpdate();
		void OnImGuiRender();

		void SetScene(std::shared_ptr<Scene> scene) noexcept { m_CurrentScene = scene; }

		[[nodiscard]] const glm::vec2 GetViewportSize() const noexcept { return m_ViewportSize; }
	private:
		std::shared_ptr<Scene> m_CurrentScene;

		std::shared_ptr<FrameBuffer> m_FrameBuffer;
		bool m_ViewportFocused = false;
		glm::vec2 m_ViewportSize{0, 0};

		void RenderScene();
	};
}
