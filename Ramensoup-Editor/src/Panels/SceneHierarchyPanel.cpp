#include "SceneHierarchyPanel.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

namespace Ramensoup
{
	SceneHierarchyPanel::SceneHierarchyPanel(std::shared_ptr<Scene> scene)
		:m_CurrentScene(scene)
	{
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");
		ImGui::Text("asdf");

		m_CurrentScene->m_Registry.each([&](auto entityID)
			{
				RenderEntity({ entityID, m_CurrentScene.get() });
			});

		ImGui::End();
	}
	void SceneHierarchyPanel::RenderEntity(const Entity& entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= (m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0;

		bool opened = ImGui::TreeNodeEx(tag.c_str(), flags);
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			m_SelectedEntity = entity;
		}
		if (opened)
		{
			ImGui::Text("List of components");
			ImGui::TreePop();
		}
	}
}