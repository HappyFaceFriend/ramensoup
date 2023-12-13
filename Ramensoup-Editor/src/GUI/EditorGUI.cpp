#include "EditorGUI.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

namespace Ramensoup
{
	bool EditorGUI::InputText(const zstring_view& label, char* buffer, size_t size)
	{
		ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue;

		ImGui::Text(label);
		ImGui::SameLine();
		ImGui::InputText("##tag", buffer, size, flags);

		if (ImGui::IsItemDeactivatedAfterEdit())
			return true;
		return false;
	}
}