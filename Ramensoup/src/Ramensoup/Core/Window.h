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

		WindowProps(const std::string& title = "window", uint32_t width = 1280, uint32_t height = 720)
			:Title(title), Width(width), Height(height)
		{}
	};
	class Window
	{
	public:
		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	public:

		virtual ~Window(){}

		virtual void OnUpdate()=0;

		virtual void SetVSync(bool enable)=0;
		virtual bool IsVSync() const=0;

		virtual uint32_t GetWidth() const=0;
		virtual uint32_t GetHeight() const=0;

		using EventCallbackFunc = std::function<void(Event&)>;
		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;

	protected:
		template <typename T>
		static void QueueEvent(T&& e) { EventQueue::Get().Push(std::move(e)); }

	protected:
		std::unique_ptr<RenderContext> m_RenderContext;
	};
}