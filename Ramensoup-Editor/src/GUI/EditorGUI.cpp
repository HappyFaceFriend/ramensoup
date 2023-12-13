#include "EditorGUI.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

#include "glm/gtc/type_ptr.hpp"

namespace Ramensoup
{
	bool EditorGUI::InputText(const zstring_view& label, char* buffer, size_t size, const char* id)
	{
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue;

		ImGui::Text(label);
		ImGui::SameLine();
		ImGui::InputText(id, buffer, size, flags);

		if (ImGui::IsItemDeactivatedAfterEdit())
			return true;
		return false;
	}
	bool EditorGUI::Vector3Field(const zstring_view& label, glm::vec3& vector, const char* id)
	{
		ImGui::Text(label);
		ImGui::SameLine();
		return ImGui::DragFloat3(id, glm::value_ptr(vector));
	}
}