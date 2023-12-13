#include "EditorGUI.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

#include "glm/gtc/type_ptr.hpp"

namespace Ramensoup
{
	bool EditorGUI::InputText(const zstring_view& label, char* buffer, size_t size)
	{
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue;

		ImGui::Text(label);
		ImGui::SameLine();
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
		ImGui::SameLine();
		ImGui::PushID(label);
		bool changed = ImGui::DragFloat3("", glm::value_ptr(vector));
		ImGui::PopID();
		return changed;
	}
}