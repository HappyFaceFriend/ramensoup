#pragma once

#include "EventQueue.h"

#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Renderer/RenderContext.h"

namespace Ramensoup
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		[[nodiscard]] WindowProps(const zstring_view& title = "window", uint32_t width = 1280, uint32_t height = 720)
			:Title(title), Width(width), Height(height)
		{}
	};

	class Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

	public:
		[[nodiscard]] Window() = default;
		virtual ~Window(){}

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

	public:
		[[nodiscard]] static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());

	public:
		virtual void OnUpdate()=0;
		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;

		virtual void SetVSync(bool enable)=0;
		[[nodiscard]] virtual bool IsVSync() const=0;

		[[nodiscard]] virtual uint32_t GetWidth() const=0;
		[[nodiscard]] virtual uint32_t GetHeight() const=0;

	protected:
		std::unique_ptr<RenderContext> m_RenderContext;
	};
}