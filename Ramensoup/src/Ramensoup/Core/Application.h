#pragma once

#include "Window.h"
#include "EventManager.h"
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

		template<typename T>
		void OnEvent(T&& e) { m_EventManager.Push(std::forward(e)); }
		void OnWindowCloseEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();

		static Application& Get() { return *instance; }

	private:
		bool m_IsRunning = false;

		LayerStack m_LayerStack;
		EventManager m_EventManager;

		std::unique_ptr<Window> m_Window;

		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
		
		static Application* instance;
	};

	//to be defined in client
	Application* CreateApplication();
}

