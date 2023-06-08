#pragma once

#include "Event.h"

namespace Ramensoup
{
	struct MouseButtonPressEvent : public Event<EventType::MouseButtonPress, EventCategory::MouseButton>
	{
		int Button;
	};
	struct MouseButtonReleaseEvent : public Event<EventType::MouseButtonRelease, EventCategory::MouseButton>
	{
		int Button;
	};
	struct MouseMoveEvent : public Event<EventType::MouseMove, EventCategory::Mouse>
	{
		float X, Y;
	};
	struct MouseScrollEvent : public Event<EventType::MouseScroll, EventCategory::Mouse>
	{
		float XOffset, YOffset;
	};
}