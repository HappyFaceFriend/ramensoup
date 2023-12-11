#pragma once

#include <glm/glm.hpp>


namespace Ramensoup
{
	class Window;

	class Input
	{
	public:
		Input() = delete;

		static void SetWindow(Window* window);
		[[nodiscard]] static bool IsKeyPressed(int keycode);
		[[nodiscard]] static bool IsMouseButtonPressed(int button);
		[[nodiscard]] static glm::vec2 GetMousePos();

	};
}