#pragma once

#include "Ramensoup/Core/Window.h"

namespace Ramensoup
{

	class ImGuiCommands
	{
	public:
		static void Init(Window* window);
		static void Shutdown();
		static void EnableDockspace();

		static void Begin();
		static void End();

		ImGuiCommands() = delete;
	};
}