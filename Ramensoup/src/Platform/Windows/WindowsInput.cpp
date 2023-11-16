#include "pch.h"
#include "Ramensoup/Core/Input.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Ramensoup
{
	static GLFWwindow* s_WindowHandle;

	void Input::SetWindow(Window* window)
	{
		s_WindowHandle = dynamic_cast<WindowsWindow*>(window)->GetWindowHandle();
	}
	bool Input::IsKeyPressed(int keycode)
	{
		auto state = glfwGetKey(s_WindowHandle, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto state = glfwGetMouseButton(s_WindowHandle, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePos()
	{
		double x, y;
		glfwGetCursorPos(s_WindowHandle, &x, &y);

		return { (float)x, (float)y };
	}
}