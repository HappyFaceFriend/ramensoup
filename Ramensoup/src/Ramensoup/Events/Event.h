#pragma once

#include "Ramensoup/Core/Utils.h"
#include "Ramensoup/Core/Logger.h"

#include <optional>

namespace Ramensoup
{
	enum class EventType
	{
		None = 0,
		AppTick, AppUpdate, AppRender,
		WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMove,
		KeyPress, KeyRelease, KeyType,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll,
		MaxValue
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

	struct Event
	{
		//T : Event, U : Handling class
		template<typename T, typename U>
		using EventHandler = bool (U::*)(const T&);

		//T : Event, U : Handling class
		//e : the event, handler : handling function, instance : the handling object (this)
		template<typename T, typename U>
		static bool Dispatch(const Event& e, EventHandler<T, U> handler, U* instance)
		{
			if (e.Type == T::GetStaticType())
				return (instance->*handler)((const T&)e);
			return false;
		}
	protected:
		EventType Type;
#ifdef RS_DEBUG
		const char* Name() const { return typeid(*this).name(); }
#else
		const char* Name() const { return "Event"; }
#endif		
	};

	template<EventType type, EventCategory categoryFlags>
	struct EventBase : public Event
	{
		EventBase() { Type = type; }
		constexpr static EventType GetStaticType() { return type; }
		constexpr EventType GetType() const  { return type; }
		constexpr bool IsInCategory(EventCategory category) const  { return (int)categoryFlags & (int)category; }
		constexpr EventCategory GetCategory() const  { return categoryFlags; }
	};
}