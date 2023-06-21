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
		using HandlerFunc  = std::function<void(T&)>;
		static void Flush(HandlerFunc callback)
		{
			for (T& event : s_Queue)
			{
				callback(event);
				if (event.IsHandled)
					break;
			}
			s_Queue.clear();
		}
		static bool IsEmpty() { return s_Queue.empty(); }
	private:
		inline static std::vector<T> s_Queue;
	};
}