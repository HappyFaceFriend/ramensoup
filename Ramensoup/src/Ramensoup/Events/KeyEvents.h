#pragma once

#include "Event.h"

namespace Ramensoup
{
	struct KeyPressEvent : public Event<EventType::KeyPress, EventCategory::Keyboard>
	{
		int KeyCode;
	};
	struct KeyReleaseEvent : public Event<EventType::KeyRelease, EventCategory::Keyboard>
	{
		int KeyCode;
	};
	struct KeyTypeEvent : public Event<EventType::KeyType, EventCategory::Keyboard>
	{
		int KeyCode;
	};
}