#include "pch.h"

#include "Application.h"
#include "Logger.h"

#include "EventQueue.h"
#include "Ramensoup/Events/WindowEvents.h"

#include "Ramensoup/ImGui/ImGuiCommands.h"
#include "imgui.h"

#include "Ramensoup/Renderer/Renderer.h"
#include "Ramensoup/Core/Input.h"

#include "Ramensoup/Core/Time.h"

namespace Ramensoup
{

	Application::Application(const std::string& name)
	{
		RS_CORE_LOG("Created Application!");
		m_Window = Window::Create({ name, 1280, 720 });
		m_Window->SetVSync(false);
		Input::SetWindow(m_Window.get());

		m_ImGuiLayer = new ImGuiLayer(m_Window.get());
		m_LayerStack.PushOverlay(m_ImGuiLayer);

		EventQueue::AddOverlayHandler<WindowCloseEvent>(std::bind(&Application::OnWindowCloseEvent, this, std::placeholders::_1));

		Renderer::Init(Renderer::API::OpenGL);
		Renderer::SetClearColor(glm::vec4(0.8f, 0.5f, 0.1f, 1.0f));
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
	bool Application::OnWindowCloseEvent(WindowCloseEvent& event)
	{
		m_IsRunning = false;
		return true;
	}
	void Application::Run()
	{
		m_IsRunning = true;

		while (m_IsRunning)
		{
			Time::Tick();
			EventQueue::Get().Flush(m_LayerStack);

			m_Window->OnUpdate();

			Renderer::Clear();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();


			ImGuiCommands::Begin();
			bool show_demo_window = true;
			ImGui::ShowDemoWindow(&show_demo_window);
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiUpdate();
			ImGuiCommands::End();

		}

	}

}