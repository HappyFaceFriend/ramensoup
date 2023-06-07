#include "pch.h"

#include "Application.h"
#include "Logger.h"



namespace Ramensoup
{
	Application::Application(const std::string& name)
	{
		CoreLogger::Log("Created Application!");
		m_Window = new Window( name, 1280, 720 );
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		m_IsRunning = true;
		while (m_IsRunning)
		{
			m_Window->OnUpdate();
		}

	}

}