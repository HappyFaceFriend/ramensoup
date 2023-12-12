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

		m_CurrentScene->m_Registry.each([&](auto entityID)
			{
				Entity entity{ entityID, m_CurrentScene.get() };
				//TODO : Should maintain a vector of root entities, using something like SetDirty()
				if (entity.GetComponent<TransformComponent>().GetParent().IsNull())
					RenderEntity(entity);
			});

		ImGui::End();
	}
	void SceneHierarchyPanel::RenderEntity(const Entity& entity)
	{
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= transformComponent.GetChildren().empty() ? ImGuiTreeNodeFlags_Leaf : 0;
		//TODO : Need to change selected entity with arrow keys
		flags |= (m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0;

		bool opened = ImGui::TreeNodeEx(tag.c_str(), flags);
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			m_SelectedEntity = entity;
		}
		if (opened)
		{
			for (auto& child : transformComponent.GetChildren())
				RenderEntity(child);
			ImGui::TreePop();
		}
	}
}