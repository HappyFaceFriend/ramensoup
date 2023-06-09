#include "pch.h"

#include "Application.h"
#include "Logger.h"



namespace Ramensoup
{
	Application::Application(const std::string& name)
	{
		CoreLogger::Log("Created Application!");
		m_Window = Window::Create({ name, 1280, 720 });
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_Window->SetVSync(true);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(EventBase& event)
	{
		//Push event to event queue
		CoreLogger::Log("{0}", event.Name());
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