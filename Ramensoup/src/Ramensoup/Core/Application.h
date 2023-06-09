#pragma once

#include "Window.h"

namespace Ramensoup
{
	class Application
	{
	public:
		Application(const std::string& name = "New Application");
		Application(const Application&) = default;
		Application& operator=(const Application&) = delete;

		virtual ~Application();

		void OnEvent(EventBase& event);

		void Run();

	private:
		bool m_IsRunning = false;

		std::unique_ptr<Window> m_Window;
	};

	//to be defined in client
	Application* CreateApplication();
}

