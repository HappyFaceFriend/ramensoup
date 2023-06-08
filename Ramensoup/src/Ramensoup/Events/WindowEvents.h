#pragma once

#include "Event.h"

namespace Ramensoup
{
	struct WindowCloseEvent : public Event<EventType::WindowClose, EventCategory::Window>
	{
		int Button;
	};
	struct WindowFocusEvent : public Event<EventType::WindowFocus, EventCategory::Window>
	{
		int Button;
	};
	struct WindowLoseFocusEvent : public Event<EventType::WindowLoseFocus, EventCategory::Window>
	{
		float X, Y;
	};
	struct WindowMoveEvent : public Event<EventType::WindowMove, EventCategory::Window>
	{
		float XOffset, YOffset;
	};
	struct WindowResizeEvent : public Event<EventType::WindowResize, EventCategory::Window>
	{
		float XOffset, YOffset;
	};
}