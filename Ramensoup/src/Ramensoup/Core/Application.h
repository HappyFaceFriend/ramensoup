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
		void QueueEvent(const T& e) { m_EventQueue.Push(e); }
		void FlushEvents();

		bool HandleEvent(const Event& e);
		bool OnWindowCloseEvent(const WindowCloseEvent& e);
		bool OnWindowResizeEvent(const WindowResizeEvent& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();
		void Close();

		inline ImGuiLayer& GetImGuiLayer() const { return *m_ImGuiLayer; }
	public:
		inline static Application& Get() { return *s_Instance;  }

	private:
		static Application* s_Instance;

		bool m_IsRunning = false;

		LayerStack m_LayerStack;
		EventQueue m_EventQueue;

		std::unique_ptr<Window> m_Window;

		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;

		
	};

	//to be defined in client
	Application* CreateApplication();

}

