#include "pch.h"

#include "Application.h"

#include "EventQueue.h"
#include "Ramensoup/Events/WindowEvents.h"

#include "Ramensoup/ImGui/ImGuiCommands.h"
#include "imgui.h"

#include "Ramensoup/Renderer/Renderer.h"
#include "Ramensoup/Core/Input.h"

#include "Ramensoup/Core/Time.h"

namespace Ramensoup
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
		:m_EventQueue()
	{
		RS_CORE_LOG("Created Application!");
		m_Window = Window::Create({ name, 1280, 720 });
		m_Window->SetVSync(false);
		Input::SetWindow(m_Window.get());

		//TODO : Only in debug mabye
		m_ImGuiLayer = std::make_unique<ImGuiLayer>(m_Window.get());
		m_LayerStack.PushOverlay(m_ImGuiLayer.get());

		m_ProfileLayer = std::make_unique<ProfileLayer>();
		m_LayerStack.PushOverlay(m_ProfileLayer.get());

		Renderer::Init(Renderer::API::OpenGL);
		Renderer::SetClearColor(glm::vec4(0.8f, 0.5f, 0.1f, 1.0f));

		s_Instance = this;
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

	bool Application::HandleEvent(const Event& e)
	{
		bool handled = false;
		handled = Event::Dispatch(e, &Application::OnWindowCloseEvent, this);
		handled = Event::Dispatch(e, &Application::OnWindowResizeEvent, this);
		return handled;
	}
	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event)
	{
		Close();
		return true;
	}
	bool Application::OnWindowResizeEvent(const WindowResizeEvent& event)
	{
		Renderer::SetViewport(0, 0, event.Width, event.Height);
		return false;
	}
	void Application::Close()
	{
		m_IsRunning = false;
	}
	void Application::Run()
	{
		m_IsRunning = true;

		while (m_IsRunning)
		{
			Time::Tick();
			m_Window->OnUpdate();

			FlushEvents();

			Renderer::Clear();

			for (auto& layer : m_LayerStack)
				layer->OnUpdate();

			ImGuiCommands::Begin();
			for (auto& layer : m_LayerStack)
				layer->OnImGuiUpdate();
			ImGuiCommands::End();
		}
	}
	void Application::FlushEvents()
	{
		while (!m_EventQueue.IsEmpty())
		{
			Event& e = m_EventQueue.Pop();
			bool handled = false;
			//Application handles first
			HandleEvent(e);
			//Pend through layerstack
			for (auto iter = m_LayerStack.cend(); iter != m_LayerStack.cbegin(); )
			{
				iter--;
				handled = (*iter)->HandleEvent(e);
				if (handled)
					break;
			}
		}
		m_EventQueue.Clear();
	}
	

}