#include "pch.h"
#include "ImGuiLayer.h"
#include "ImGuiCommands.h"

#include <imgui.h>

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