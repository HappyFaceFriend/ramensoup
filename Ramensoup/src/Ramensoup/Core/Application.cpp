#include "pch.h"

#include "Application.h"


namespace Ramensoup
{
	Application::Application(const std::string& name)
	{
		std::cout << "Created application "<< name << std::endl;
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_IsRunning = true;
		while (m_IsRunning)
		{
			std::cout << "Running application" << std::endl;
		}
	}

}