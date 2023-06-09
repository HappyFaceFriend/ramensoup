#include "pch.h"

#include "Application.h"
#include "Logger.h"

#include "EventQueue.h"
#include "Ramensoup/Events/WindowEvents.h"


namespace Ramensoup
{
	Application::Application(const std::string& name)
		:m_EventManager(&m_LayerStack)
	{
		CoreLogger::Log("Created Application!");
		m_Window = Window::Create({ name, 1280, 720 });
		m_Window->SetVSync(true);
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
	void Application::OnWindowCloseEvent(Event& event)
	{
		m_IsRunning = false;
	}
	void Application::Run()
	{
		m_IsRunning = true;
		while (m_IsRunning)
		{
			m_EventManager.Flush();
			EventQueue<WindowCloseEvent>::Flush(std::bind(&Application::OnWindowCloseEvent, this, std::placeholders::_1));

			m_Window->OnUpdate();

		}

	}

}