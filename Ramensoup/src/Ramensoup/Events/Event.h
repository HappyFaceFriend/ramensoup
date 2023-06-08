#pragma once

#include "Ramensoup/Core/Utils.h"

namespace Ramensoup
{
	enum class EventType
	{
		None = 0,
		AppTick, AppUpdate, AppRender,
		WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMove,
		KeyPress, KeyRelease, KeyType,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	};

	enum class EventCategory : int
	{
		None = 0,
		Application = BIT(0),
		Window		= BIT(1),
		Input		= BIT(2),
		Keyboard	= BIT(3) | Input,
		Mouse		= BIT(4) | Input,
		MouseButton = BIT(5) | Input | Mouse,
	};
	
	struct EventBase
	{
		bool IsHandled = true;
	};

	template<EventType type, EventCategory categoryFlags>
	struct Event : EventBase
	{
		inline EventType GetType() const { return type; }
		inline bool IsInCategory(EventCategory category) const { return categoryFlags & category; }
		inline EventCategory GetCategory() const { return categories; }
	};
}