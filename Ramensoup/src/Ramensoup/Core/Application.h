#pragma once

#include "Window.h"
#include "EventManager.h"
#include "LayerStack.h"

namespace Ramensoup
{
	class Application
	{
	public:
		Application(const std::string& name = "New Application");
		Application(const Application&) = default;
		Application& operator=(const Application&) = delete;

		virtual ~Application();

		void OnWindowCloseEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();

	private:
		bool m_IsRunning = false;

		LayerStack m_LayerStack;
		EventManager m_EventManager;

		std::unique_ptr<Window> m_Window;
	};

	//to be defined in client
	Application* CreateApplication();
}

