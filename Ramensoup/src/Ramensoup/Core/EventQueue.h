#pragma once

#include "Ramensoup/Events/Event.h"

namespace Ramensoup
{
	template <typename T>
	class EventAllocator
	{
	public:
		static T* Allocate(T&& e)
		{
			s_Buffer.push_back(std::forward<T>(e));
			return &(s_Buffer.back());
		}
		static void Flush()
		{
			s_Buffer.clear();
		}
	private:
		inline static std::vector<T> s_Buffer;
	};

	//TODO: Need to clear the buffers every flush.
	class EventQueue
	{
	public:
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

		template <typename T>
		static void Push(T&& e)
		{
			T* allocatedEvent = EventAllocator<T>::Allocate(std::move(e));
			m_Queue.push_back(std::make_unique<T>(allocatedEvent));
		}
		static void Flush(std::function<void(Event&)> handler);
	private:
		static std::vector<std::unique_ptr<Event>> m_Queue;
	};
}