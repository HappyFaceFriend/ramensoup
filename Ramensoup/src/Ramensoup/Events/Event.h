#pragma once


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
		Application = (1 << 0),
		Window	    = (1 << 1),
		Input		= (1 << 2),
		Keyboard    = (1 << 3) | Input,
		Mouse       = (1 << 4) | Input,
		MouseButton = (1 << 5) | Input | Mouse,
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
				return (instance->*handler)(static_cast<const T&>(e));
			return false;
		}
		bool IsInCategory(EventCategory category) const { return static_cast<int>(m_CategoryFlags) & static_cast<int>(category); }
	protected:
		Event(EventType type, EventCategory category)
		:m_Type(type), m_CategoryFlags(category)
		{
		}

		~Event() = default;
		Event(const Event&) = default;
		Event(Event&&) = default;
		Event& operator=(const Event&) = default;
		Event& operator=(Event&&) = default;

	private:
		const EventType m_Type;
		const EventCategory m_CategoryFlags;
	};

	template<EventType type, EventCategory categoryFlags>
	struct EventBase : public Event
	{
	protected:
		EventBase() : Event(type, categoryFlags) {  }
	public:
		constexpr static EventType GetStaticType() { return type; }
		constexpr EventType GetType() const  { return type; }
		constexpr bool IsInCategory(EventCategory category) const  { return (int)categoryFlags & (int)category; }
		constexpr EventCategory GetCategory() const  { return categoryFlags; }
	};
}