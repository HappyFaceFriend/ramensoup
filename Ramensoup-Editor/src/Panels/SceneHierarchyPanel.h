#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel(std::shared_ptr<Scene> scene);
		
		void OnImGuiRender();

		inline void SetScene(std::shared_ptr<Scene> scene) noexcept { m_CurrentScene = scene; }

	private:
		std::shared_ptr<Scene> m_CurrentScene;
		Entity m_SelectedEntity{};

		void RenderEntity(const Entity& entity);
	};
}