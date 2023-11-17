#include "pch.h"
#include "ProfileLayer.h"

#include <imgui.h>

namespace Ramensoup
{
	void ProfileLayer::OnImGuiUpdate()
	{
		//Test windows
		ImGui::Begin("Debug Profiler");
		ImGui::Text("Hello world");
		ImGui::End();

	}
}