#pragma once

#include <GLFW/glfw3.h>

#include "Ramensoup/Core/Window.h"

namespace Ramensoup
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Data.Width; }
		virtual uint32_t GetHeight() const override { return m_Data.Height; }

		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return m_Data.VSyncEnabled; }

		inline GLFWwindow* GetWindowHandle() const{ return m_WindowHandle; }

	private:
		virtual void InitEventCallbacks();
		virtual void Shutdown();
	private:
		GLFWwindow* m_WindowHandle;

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;
			bool VSyncEnabled;
		} m_Data;
	};
}