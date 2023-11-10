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
		// TODO : Block events
		return false;
	}




}