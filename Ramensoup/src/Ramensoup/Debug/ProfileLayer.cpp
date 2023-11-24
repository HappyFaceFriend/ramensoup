#include "pch.h"
#include "ProfileLayer.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

#include "TimeProfiler.h"

namespace Ramensoup
{
	void ProfileLayer::OnImGuiUpdate()
	{
		ImGui::Begin("Time Profiler");
		for (const auto& key : TimeProfiler::Get().GetProfileKeys())
		{
			ImGui::Text("%s: %lfms", key.c_str(), TimeProfiler::Get().GetProfileItem(key).Miliseconds);
			ImGui::Spacing();
		}
		ImGui::End();

	}
}