#include "pch.h"

#include "Application.h"
#include "Logger.h"

#include <GLFW/glfw3.h>


namespace Ramensoup
{
	GLFWwindow* window;
	Application::Application(const std::string& name)
	{
		CoreLogger::Log("Created Application!");

		//TEMP : GLFW code
		if (!glfwInit())
		{
			CoreLogger::Error("GLFW init failed!");
		}

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
		if (!window)
		{
			CoreLogger::Error("Window creation failed!");
			glfwTerminate();

		}

		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_IsRunning = true;
		while (!glfwWindowShouldClose(window))
		{

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
	}

}