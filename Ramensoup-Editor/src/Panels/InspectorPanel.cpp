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
			DrawComponent<CameraComponent>("Camera", m_CurrentEntity, [](CameraComponent& component)
				{
					auto& projection = component.Projection;
					const char* projectionTypeStrings[2] = { "Perspective", "Orthographic" };
					const char* currentProjectionTypeString = projectionTypeStrings[(int)projection.GetProjectionType()];

					if (ImGui::BeginCombo("Projection Type", currentProjectionTypeString))
					{
						for (int i = 0; i < 2; i++)
						{
							bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
							if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
							{
								currentProjectionTypeString = projectionTypeStrings[i];
								projection.SetProjectionType((CameraProjection::Type)i);
							}
							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (projection.GetProjectionType() == CameraProjection::Type::Perspective)
					{
						float perspectiveVerticalFov = glm::degrees(projection.GetPerspectiveVerticalFOV());
						if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
							projection.SetPerspectiveVerticalFOV(glm::radians(perspectiveVerticalFov));

						float perspectiveNear = projection.GetPerspectiveNearClip();
						if (ImGui::DragFloat("Near", &perspectiveNear))
							projection.SetPerspectiveNearClip(perspectiveNear);

						float perspectiveFar = projection.GetPerspectiveFarClip();
						if (ImGui::DragFloat("Far", &perspectiveFar))
							projection.SetPerspectiveFarClip(perspectiveFar);
					}
					else //Orthographic
					{
						float orthoSize = projection.GetOrthographicSize();
						if (ImGui::DragFloat("Size", &orthoSize))
							projection.SetOrthographicSize(orthoSize);

						float orthoNear = projection.GetOrthographicNearClip();
						if (ImGui::DragFloat("Near", &orthoNear))
							projection.SetOrthographicNearClip(orthoNear);

						float orthoFar = projection.GetOrthographicFarClip();
						if (ImGui::DragFloat("Far", &orthoFar))
							projection.SetOrthographicFarClip(orthoFar);
					}
				});
		}
		else
		{
			ImGui::Text("No entity selected");
		}
		ImGui::End();
	}

}