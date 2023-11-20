#pragma once
#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Core/EventQueue.h"

#include "Ramensoup/Renderer/RenderContext.h"

namespace Ramensoup
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string_view& title = {"window"}, uint32_t width = 1280, uint32_t height = 720)
			:Title(title), Width(width), Height(height)
		{}
	};
	class Window
	{
	public:
		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	public:
		Window() = default;
		virtual ~Window(){}

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		virtual void OnUpdate()=0;

		virtual void SetVSync(bool enable)=0;
		virtual bool IsVSync() const=0;

		virtual uint32_t GetWidth() const=0;
		virtual uint32_t GetHeight() const=0;

		using EventCallbackFunc = std::function<void(Event&)>;
		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;

	protected:
		std::unique_ptr<RenderContext> m_RenderContext;
	};
}