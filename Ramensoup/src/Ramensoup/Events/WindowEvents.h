#pragma once

#include "Event.h"

namespace Ramensoup
{
	struct WindowCloseEvent : public Event<EventType::WindowClose, EventCategory::Window>
	{
	};
	struct WindowFocusEvent : public Event<EventType::WindowFocus, EventCategory::Window>
	{
	};
	struct WindowLoseFocusEvent : public Event<EventType::WindowLoseFocus, EventCategory::Window>
	{
	};
	struct WindowResizeEvent : public Event<EventType::WindowResize, EventCategory::Window>
	{
		int Width, Height;
		WindowResizeEvent(int width, int height) :Width(width), Height(height) {}
	};
}