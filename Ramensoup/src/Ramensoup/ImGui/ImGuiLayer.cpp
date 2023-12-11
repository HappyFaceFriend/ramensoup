#include "pch.h"
#include "ImGuiLayer.h"

#include "ImGuiCommands.h"

#pragma warning(push)
#pragma warning(disable:4819 4005 4996)
#include <imgui.h>
#pragma warning(pop)

namespace Ramensoup
{
	ImGuiLayer::ImGuiLayer(Window *window)
		: Layer("ImGui Layer")
	{
		ImGuiCommands::Init(window);
	}

	ImGuiLayer::~ImGuiLayer()
	{
		ImGuiCommands::Shutdown();
	}

	bool ImGuiLayer::HandleEvent(const Event& e)
	{
		bool handled = false;
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			handled |=  (e.IsInCategory(EventCategory::Mouse) & io.WantCaptureMouse);
			handled |=  (e.IsInCategory(EventCategory::Keyboard) & io.WantCaptureKeyboard);
		}
		return handled;
	}
}