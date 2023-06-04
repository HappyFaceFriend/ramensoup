#pragma once


namespace Ramensoup
{
	class Application
	{
	public:
		Application(const std::string& name = "New Application");
		Application(const Application&) = default;
		Application& operator=(const Application&) = delete;

		virtual ~Application();

		void Run();

	private:
		bool m_IsRunning = false;
	};

	//to be defined in client
	Application* CreateApplication();
}

