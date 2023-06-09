#pragma once

#include "Event.h"

namespace Ramensoup
{
	struct WindowCloseEvent : public EventBase<EventType::WindowClose, EventCategory::Window>
	{
	};
	struct WindowFocusEvent : public EventBase<EventType::WindowFocus, EventCategory::Window>
	{
	};
	struct WindowLoseFocusEvent : public EventBase<EventType::WindowLoseFocus, EventCategory::Window>
	{
	};
	struct WindowResizeEvent : public EventBase<EventType::WindowResize, EventCategory::Window>
	{
		int Width, Height;
		WindowResizeEvent(int width, int height) :Width(width), Height(height) {}
	};
}