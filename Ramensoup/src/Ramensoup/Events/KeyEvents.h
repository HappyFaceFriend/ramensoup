#pragma once

#include "Event.h"

namespace Ramensoup
{
	struct KeyPressEvent : public EventBase<EventType::KeyPress, EventCategory::Keyboard>
	{
		int KeyCode;
		KeyPressEvent(int keyCode) : KeyCode(keyCode){}
	};
	struct KeyReleaseEvent : public EventBase<EventType::KeyRelease, EventCategory::Keyboard>
	{
		int KeyCode;
		KeyReleaseEvent(int keyCode) : KeyCode(keyCode) {}
	};
	struct KeyTypeEvent : public EventBase<EventType::KeyType, EventCategory::Keyboard>
	{
		int KeyCode;
		KeyTypeEvent(int keyCode) : KeyCode(keyCode) {}
	};
}