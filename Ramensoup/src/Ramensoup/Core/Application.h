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

		template <typename T>
		void QueueEvent(T&& e) { m_EventQueue.Push(std::move(e)); }
		void HandleEvents();

		bool OnWindowCloseEvent(WindowCloseEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();
	public:
		inline static Application& Get() { return *s_Instance;  }

	private:
		static Application* s_Instance;

		bool m_IsRunning = false;

		LayerStack m_LayerStack;
		EventQueue m_EventQueue;

		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		
	};

	//to be defined in client
	Application* CreateApplication();

}

