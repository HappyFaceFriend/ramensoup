#include "pch.h"
#include "WindowsWindow.h"

#include "Ramensoup/Core/Logger.h"

namespace Ramensoup
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		CoreLogger::Error("GLFW Error {0} : {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
		:m_Data{ props.Title, props.Width, props.Height, false }
	{
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			//assert success
			s_GLFWInitialized = true;
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		m_WindowHandle = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), NULL, NULL);
		if (!m_WindowHandle)
		{
			CoreLogger::Error("Window creation failed!");
			glfwTerminate();

		}
		glfwMakeContextCurrent(m_WindowHandle);

		glfwSetWindowUserPointer(m_WindowHandle, &m_Data);

	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(m_WindowHandle);
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSyncEnabled = enable;

	}

	void WindowsWindow::InitEventCallbacks()
	{
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_WindowHandle);
	}


}