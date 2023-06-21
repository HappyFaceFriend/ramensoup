#include "pch.h"

#include "Application.h"
#include "Logger.h"

#include "EventQueue.h"
#include "Ramensoup/Events/WindowEvents.h"

#include "Ramensoup/ImGui/ImGuiCommands.h"
#include "imgui.h"
//TEMP
#include "glad/glad.h"

namespace Ramensoup
{
	Application::Application(const std::string& name)
		:m_EventManager(&m_LayerStack)
	{
		CoreLogger::Log("Created Application!");
		m_Window = Window::Create({ name, 1280, 720 });
		m_Window->SetVSync(true);

		m_ImGuiLayer = std::make_unique<ImGuiLayer>(m_Window.get());
		m_LayerStack.PushOverlay(m_ImGuiLayer.get());
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
			EventQueue<WindowCloseEvent>::Flush(std::bind(&Application::OnWindowCloseEvent, this, std::placeholders::_1));
			m_EventManager.Flush();

			m_Window->OnUpdate();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//TEMP
			glClearColor(0.8, 0.5, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			ImGuiCommands::Begin();
			bool show_demo_window = true;
			ImGui::ShowDemoWindow(&show_demo_window);
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiUpdate();
			ImGuiCommands::End();

		}

	}

}