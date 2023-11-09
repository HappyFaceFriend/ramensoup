#pragma once

#include "Ramensoup/Core/Utils.h"
#include "Ramensoup/Core/Logger.h"

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
		using EventCallbackFunc = std::function<void(Event&)>;


#ifdef RS_DEBUG
		const char* Name() const { return typeid(*this).name(); }
#else
		const char* Name() const { return "Event"; }
#endif		
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_Event(e){}
		template<typename T>
		using EventHandler = std::function<bool(T&)>;

		template<typename T>
		void Dispatch(EventHandler<T> func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.IsHandled = func(*(T*)&m_Event);
			}
		}
	private:
		Event& m_Event;
	};
	template<EventType type, EventCategory categoryFlags>
	struct EventBase : public Event
	{
		constexpr static EventType GetStaticType() { return type; }
		constexpr EventType GetType() const  { return type; }
		constexpr bool IsInCategory(EventCategory category) const  { return (int)categoryFlags & (int)category; }
		constexpr EventCategory GetCategory() const  { return categoryFlags; }
	};
}