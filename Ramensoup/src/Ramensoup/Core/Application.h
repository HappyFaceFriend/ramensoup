#pragma once

#include "Window.h"
#include "EventQueue.h"
#include "LayerStack.h"

#include "Ramensoup/ImGui/ImGuiLayer.h"
#include "Ramensoup/Debug/ProfileLayer.h"

namespace Ramensoup
{

	class Application
	{
	protected:
		//TODO : Can be created twice..
		[[nodiscard]] Application(const zstring_view& name =  "New Application" );

	public:
		virtual ~Application() = default;
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		template <typename T>
		void QueueEvent(const T& e) { m_EventQueue.Push(e); }
		void FlushEvents();

		bool HandleEvent(const Event& e);
		bool OnWindowCloseEvent(const WindowCloseEvent& e);
		bool OnWindowResizeEvent(const WindowResizeEvent& e);

		void PushLayer(const std::shared_ptr<Layer>& layer);
		void PushOverlay(const std::shared_ptr<Layer>& overlay);

		void Run();
		void Close();

		[[nodiscard]] inline ImGuiLayer& GetImGuiLayer() const { return *m_ImGuiLayer; }

		[[nodiscard]] inline static Application& Get() { return *s_Instance;  }

	private:
		static Application* s_Instance;

		bool m_IsRunning = false;

		LayerStack m_LayerStack;
		EventQueue m_EventQueue;

		std::unique_ptr<Window> m_Window;

		//TODO : Only in debug mabye
		std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
		std::shared_ptr<ProfileLayer> m_ProfileLayer;
	};

	//to be defined in client
	Application* CreateApplication();

}

