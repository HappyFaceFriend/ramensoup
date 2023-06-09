#pragma once

#include "Ramensoup/Events/Event.h"

namespace Ramensoup
{
	template <typename T>
	class EventQueue
	{
	public:

		static void Push(T&& event)
		{
			s_Queue.push_back(std::forward<T>(event));
		}
		//TODO : Make specific Flush for specific event type, so caller can make different callbacks for different events
		static void Flush(Event::EventCallbackFunc callback)
		{
			for (T& event : s_Queue)
			{
				callback(event);
				if (event.IsHandled)
					break;
			}
			s_Queue.clear();
		}
	private:
		inline static std::vector<T> s_Queue;
	};
}