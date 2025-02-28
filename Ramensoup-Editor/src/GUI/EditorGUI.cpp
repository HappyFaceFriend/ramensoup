#include "EditorGUI.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

#include "glm/gtc/type_ptr.hpp"

namespace Ramensoup
{
	uint32_t EditorGUI::s_LabelWidth = 150;

	bool EditorGUI::InputText(const zstring_view& label, char* buffer, size_t size)
	{
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue;

		ImGui::Text(label);
		ImGui::SameLine(s_LabelWidth);
		ImGui::PushID(label);
		ImGui::InputText("", buffer, size, flags);
		ImGui::PopID();
		if (ImGui::IsItemDeactivatedAfterEdit())
			return true;
		return false;
	}
	bool EditorGUI::Vector3Field(const zstring_view& label, glm::vec3& vector)
	{
		ImGui::Text(label);
		ImGui::SameLine(s_LabelWidth);
		ImGui::PushID(label);
		bool changed = ImGui::DragFloat3("", glm::value_ptr(vector));
		ImGui::PopID();
		return changed;
	}

	bool EditorGUI::ColorField(const zstring_view& label, glm::vec3& color)
	{
		ImGui::Text(label);
		ImGui::SameLine(s_LabelWidth);
		ImGui::PushID(label);
		bool changed = ImGui::ColorEdit3("", glm::value_ptr(color));
		ImGui::PopID();
		return changed;
	}

	bool EditorGUI::ColorField(const zstring_view& label, glm::vec4& color)
	{
		ImGui::Text(label);
		ImGui::SameLine(s_LabelWidth);
		ImGui::PushID(label);
		bool changed = ImGui::ColorEdit4("", glm::value_ptr(color));
		ImGui::PopID();
		return changed;
	}

	bool EditorGUI::DraggableFloatField(const zstring_view& label, float *value)
	{
		ImGui::Text(label);
		ImGui::SameLine(s_LabelWidth);
		ImGui::PushID(label);
		bool changed = ImGui::DragFloat("", value);
		ImGui::PopID();
		return changed;
	}

	bool EditorGUI::SelectableField(const zstring_view& label, const char* options[], uint32_t optionCount, uint32_t& selectedIndex)
	{
		ImGui::Text(label);
		ImGui::SameLine(s_LabelWidth);
		ImGui::PushID(label);
		bool changed = false;
		if (ImGui::BeginCombo("", options[selectedIndex]))
		{
			for (uint32_t i = 0; i < optionCount; i++)
			{
				bool isSelected = i == selectedIndex;
				if (ImGui::Selectable(options[i], isSelected))
				{
					selectedIndex = i;
					changed = true;
				}
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::PopID();
		return changed;
	}
}