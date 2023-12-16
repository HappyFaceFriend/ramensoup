#include "InspectorPanel.h"

#include "GUI/EditorGUI.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

#include "glm/gtc/type_ptr.hpp"

namespace Ramensoup
{

	template<typename T, typename DrawFunction>
	static void DrawComponent(const zstring_view& name, Entity& entity, DrawFunction drawFunction)
	{
		if (entity.HasComponent<T>())
		{
			constexpr ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
			auto& component = entity.GetComponent<T>();
			bool open = ImGui::TreeNodeEx(name, treeNodeFlags);
			if (open)
			{
				drawFunction(component);
				ImGui::TreePop();
			}
		}
	}

	void InspectorPanel::OnImGuiRender()
	{
		ImGui::Begin("Inspector");

		if (m_CurrentEntity)
		{
			auto& tag = m_CurrentEntity.GetComponent<TagComponent>().Tag;
			char tagBuffer[256];
			strcpy(tagBuffer, tag.c_str());

			if (EditorGUI::InputText("Tag", tagBuffer, sizeof(tagBuffer)))
			{
				tag = std::string(tagBuffer);
			}
			DrawComponent<TransformComponent>("Transform", m_CurrentEntity, [](TransformComponent& component)
				{
					EditorGUI::Vector3Field("Position", component.Position);
					auto rotationInDegrees = glm::degrees(component.Rotation);
					if (EditorGUI::Vector3Field("Rotation", rotationInDegrees))
						component.Rotation = glm::radians(rotationInDegrees);
					EditorGUI::Vector3Field("Scale   ", component.Scale); // TODO : Match alignment
				});
			DrawComponent<MeshRendererComponent>("Mesh Renderer", m_CurrentEntity, [](MeshRendererComponent& component)
				{
					ImGui::Text("Mesh");
					ImGui::Indent();
					ImGui::Text("File name: %s", component.Mesh->GetFilePath().c_str());
					ImGui::Text("Mesh name: %s", component.Mesh->GetName().c_str());
					ImGui::Unindent();

					ImGui::Text("Material");
					ImGui::Indent();
					ImGui::Text("Shader: %s", component.Material->GetShader()->GetName().c_str());
					ImGui::Unindent();
				});
		}
		else
		{
			ImGui::Text("No entity selected");
		}
		ImGui::End();
	}

}