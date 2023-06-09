#include "pch.h"
#include "WindowsWindow.h"

#include "Ramensoup/Core/Logger.h"

#include "Ramensoup/Events/WindowEvents.h"
#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"

namespace Ramensoup
{
	static bool s_GLFWInitialized = false;

	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
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

		InitEventCallbacks();

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
		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				QueueEvent(WindowResizeEvent(width,height));
			});
		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				QueueEvent(WindowCloseEvent());
			});
		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS: case GLFW_REPEAT:
				{
					QueueEvent(KeyPressEvent(key));
					break;
				}
				case GLFW_RELEASE:
				{
					QueueEvent(KeyReleaseEvent(key));
					break;
				}
				}
			});
		glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, unsigned int character)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				QueueEvent(KeyTypeEvent(character));
			});
		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					QueueEvent(MouseButtonPressEvent(button));
					break;
				}
				case GLFW_RELEASE:
				{
					QueueEvent(MouseButtonReleaseEvent(button));
					break;
				}
				}
			});

		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				EventQueue<MouseScrollEvent>::Push(MouseScrollEvent((float)xOffset, (float)yOffset));
			});
		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				EventQueue<MouseMoveEvent>::Push(MouseMoveEvent((float)xPos, (float)yPos));
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_WindowHandle);
	}


}