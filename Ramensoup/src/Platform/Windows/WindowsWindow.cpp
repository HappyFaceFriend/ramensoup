#include "pch.h"
#include "Ramensoup/Core/Window.h"

#include <GLFW/glfw3.h>

#include "Ramensoup/Core/Logger.h"

namespace Ramensoup
{
	static bool s_GLFWInitialized = false;

	//TEMP : This shoudn't be static
	static GLFWwindow* s_Window;

	static void GLFWErrorCallback(int error, const char* description)
	{
		CoreLogger::Error("GLFW Error {0} : {1}", error, description);
	}

	Window::Window(const std::string& title, uint32_t width, uint32_t height)
		:m_Title(title), m_Width(width), m_Height(height), m_VSyncEnabled(false)
	{
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			//assert success
			s_GLFWInitialized = true;
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		s_Window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
		if (!s_Window)
		{
			CoreLogger::Error("Window creation failed!");
			glfwTerminate();

		}

		glfwMakeContextCurrent(s_Window);

	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers(s_Window);
		glfwPollEvents();
	}

	void Window::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_VSyncEnabled = enable;

	}
	bool Window::IsVSync() const
	{
		return m_VSyncEnabled;
	}


}