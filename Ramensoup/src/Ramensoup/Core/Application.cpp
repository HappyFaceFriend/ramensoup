#include "pch.h"

#include "Application.h"
#include "Logger.h"


namespace Ramensoup
{
	Application::Application(const std::string& name)
	{
		CoreLogger::Log("Created Application!");
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_IsRunning = true;
		while (m_IsRunning)
		{

		}
	}

}