#include "pch.h"
#include "WindowsWindow.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include "Ramensoup/Events/WindowEvents.h"
#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Core/Application.h"



namespace Ramensoup
{
	static bool s_GLFWInitialized = false;

	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		RS_CORE_LOG_ERROR("GLFW Error {0} : {1}", error, description);
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
			RS_CORE_LOG_ERROR("Window creation failed!");
			glfwTerminate();
		}

		//RenderAPI Dependent
		m_RenderContext = std::make_unique<OpenGLContext>(m_WindowHandle);

		m_RenderContext->Init();

		glfwSetWindowUserPointer(m_WindowHandle, &m_Data);

		InitEventCallbacks();

	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		m_RenderContext->SwapBuffers();
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

	void WindowsWindow::SetEventCallback(const EventCallbackFunc& callback)
	{
		m_Data.EventCallback = callback;
	}

	void WindowsWindow::InitEventCallbacks()
	{
		glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				Application::Get().QueueEvent(WindowResizeEvent(width,height));
				Application::Get().FlushEvents();
			});
		glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				Application::Get().QueueEvent(WindowCloseEvent());
			});
		glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS: case GLFW_REPEAT:
				{
					Application::Get().QueueEvent(KeyPressEvent(key));
					break;
				}
				case GLFW_RELEASE:
				{
					Application::Get().QueueEvent(KeyReleaseEvent(key));
					break;
				}
				}
			});
		glfwSetCharCallback(m_WindowHandle, [](GLFWwindow* window, unsigned int character)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				Application::Get().QueueEvent(KeyTypeEvent(character));
			});
		glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					Application::Get().QueueEvent(MouseButtonPressEvent(button));
					break;
				}
				case GLFW_RELEASE:
				{
					Application::Get().QueueEvent(MouseButtonReleaseEvent(button));
					break;
				}
				}
			});
		glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				Application::Get().QueueEvent(MouseScrollEvent((float)xOffset, (float)yOffset));
			});
		glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				Application::Get().QueueEvent(MouseMoveEvent((float)xPos, (float)yPos));
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_WindowHandle);
	}


}