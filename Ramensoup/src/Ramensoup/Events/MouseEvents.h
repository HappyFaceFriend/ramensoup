#pragma once

#include "Event.h"

namespace Ramensoup
{
	struct MouseButtonPressEvent : public EventBase<EventType::MouseButtonPress, EventCategory::MouseButton>
	{
		int Button;
		MouseButtonPressEvent(int button) : Button(button) {}

	};
	struct MouseButtonReleaseEvent : public EventBase<EventType::MouseButtonRelease, EventCategory::MouseButton>
	{
		int Button;
		MouseButtonReleaseEvent(int button) : Button(button) {}
	};
	struct MouseMoveEvent : public EventBase<EventType::MouseMove, EventCategory::Mouse>
	{
		float X, Y;
		MouseMoveEvent(float x, float y) : X(x), Y(y) {}
	};
	struct MouseScrollEvent : public EventBase<EventType::MouseScroll, EventCategory::Mouse>
	{
		float XOffset, YOffset;
		MouseScrollEvent(float xOffset, float yOffset) : XOffset(xOffset), YOffset(yOffset) {}
	};
}