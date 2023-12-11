#pragma once

#include "Ramensoup/Core/Window.h"

#pragma warning(push)
#pragma warning(disable:4819)
#include <GLFW/glfw3.h>
#pragma warning(pop)

namespace Ramensoup
{
	class WindowsWindow : public Window
	{
	public:
		[[nodiscard]] WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow(WindowsWindow&&) = delete;
		WindowsWindow& operator=(const WindowsWindow&) = delete;
		WindowsWindow& operator=(WindowsWindow&&) = delete;

		void OnUpdate() override;

		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVSync() const override { return m_Data.VSyncEnabled; }

		[[nodiscard]] uint32_t GetWidth() const override { return m_Data.Width; }
		[[nodiscard]] uint32_t GetHeight() const override { return m_Data.Height; }
		[[nodiscard]] inline GLFWwindow* GetWindowHandle() const{ return m_WindowHandle; }

	private:
		GLFWwindow* m_WindowHandle;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSyncEnabled;
			EventCallbackFunc EventCallback;
		} m_Data;

	private:
		void InitEventCallbacks();
		void Shutdown();
		void SetEventCallback(const EventCallbackFunc& callback) override;
	};
}