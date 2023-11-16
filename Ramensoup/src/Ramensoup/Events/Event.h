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
			if (e.m_Type == T::GetStaticType())
				return (instance->*handler)((const T&)e);
			return false;
		}
		bool IsInCategory(EventCategory category) const { return (int)m_CategoryFlags & (int)category; }
	protected:
		Event(EventType type, EventCategory category)
		:m_Type(type), m_CategoryFlags(category)
		{
		}
	private:
		const EventType m_Type;
		const EventCategory m_CategoryFlags;
	};

	template<EventType type, EventCategory categoryFlags>
	struct EventBase : public Event
	{
		EventBase() : Event(type, categoryFlags) {  }
		constexpr static EventType GetStaticType() { return type; }
		constexpr EventType GetType() const  { return type; }
		constexpr bool IsInCategory(EventCategory category) const  { return (int)categoryFlags & (int)category; }
		constexpr EventCategory GetCategory() const  { return categoryFlags; }
	};
}