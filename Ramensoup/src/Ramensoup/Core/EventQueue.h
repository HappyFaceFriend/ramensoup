#pragma once

#include "Ramensoup/Events/Event.h"

namespace Ramensoup
{
	template <typename T>
	class EventQueue
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		static void Push(T&& event)
		{
			s_Queue.push_back(std::forward<T>(event));
		}
		static void Flush(EventCallbackFunc callback)
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