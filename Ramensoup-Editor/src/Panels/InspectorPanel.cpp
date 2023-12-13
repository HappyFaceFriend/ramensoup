#include "InspectorPanel.h"

#include "GUI/EditorGUI.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

namespace Ramensoup
{
	void InspectorPanel::OnImGuiRender()
	{
		ImGui::Begin("Inspector");

		if (m_CurrentEntity)
		{
			auto& tag = m_CurrentEntity.GetComponent<TagComponent>().Tag;
			//ImGui::Text("%s", tag.c_str());
			char tagBuffer[256];
			strcpy(tagBuffer, tag.c_str());
			
			if (EditorGUI::InputText("Tag", tagBuffer, sizeof(tagBuffer)))
			{
				tag = std::string(tagBuffer);
			}

		}
		else
		{
			ImGui::Text("No entity selected");
		}
		ImGui::End();
		ImGui::ShowDemoWindow();
	}
}