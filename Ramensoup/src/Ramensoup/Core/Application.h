#pragma once

#include "Window.h"
#include "EventQueue.h"
#include "LayerStack.h"
#include "Ramensoup/ImGui/ImGuiLayer.h"

namespace Ramensoup
{

	class Application
	{
	public:
		Application(const std::string& name = "New Application");
		Application(const Application&) = default;
		Application& operator=(const Application&) = delete;

		virtual ~Application();


		bool OnWindowCloseEvent(WindowCloseEvent& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();


	private:
		bool m_IsRunning = false;

		LayerStack m_LayerStack;


		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;
		
	};

	//to be defined in client
	Application* CreateApplication();

}

