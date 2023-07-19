#pragma once

#include <glm/glm.hpp>


namespace Ramensoup
{
	class Window;

	class Input
	{
	public:
		static void SetWindow(Window* window);
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static glm::vec2 GetMousePos();
	};
}