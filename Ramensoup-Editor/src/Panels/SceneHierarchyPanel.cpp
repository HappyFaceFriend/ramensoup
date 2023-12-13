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
				//TODO : Should maintain a vector of root entities, using something like SetDirty() to maintain order
				if (entity.GetComponent<RelationshipComponent>().GetParent().IsNull())
				{
					RenderEntity(entity);
				}
			});

		ImGui::End();
	}
	void SceneHierarchyPanel::RenderEntity(const Entity& entity)
	{
		auto& relationshipComponent = entity.GetComponent<RelationshipComponent>();
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= relationshipComponent.GetFirstChild().IsNull() ? ImGuiTreeNodeFlags_Leaf : 0;
		//TODO : Need to change selected entity with arrow keys
		flags |= (m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0;

		bool opened = ImGui::TreeNodeEx(tag.c_str(), flags);
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			m_SelectedEntity = entity;
		}
		if (opened)
		{
			auto current = relationshipComponent.GetFirstChild();
			while(!current.IsNull())
			{
				RenderEntity(current);
				current = current.GetComponent<RelationshipComponent>().GetNextSibling();
			}
			ImGui::TreePop();
		}
	}
}