#pragma once

#include "Ramensoup/Events/Event.h"

namespace Ramensoup
{
	/*
		This EventQueue stores different types of events in a single queue.
		It is achived by saving the event's type (EventType) as a header of each event.
	*/
	class EventQueue
	{
	public:
		EventQueue();
		~EventQueue();

		using EventHandler = std::function<void(Event&)>;

		template <typename T>
		void SetHandler(EventHandler handler)
		{
			m_Handlers[T::GetStaticType()] = handler;
		}

		template <typename T>
		void Push(T&& e)
		{
			//Store size of the event
			*(EventType*)m_BufferPtr = T::GetStaticType();
			m_BufferPtr = (char*)m_BufferPtr + sizeof(EventType*);
			//Store actual event
			*(T*)m_BufferPtr = std::move<T>(e);		//TODO : Test if copy constructor is called
			m_BufferPtr = (char*)m_BufferPtr + PaddedSizeof<T>();
		}

		void Flush();
		

	private:
		template<typename T>
		static uint32_t PaddedSizeof()
		{
			return sizeof(T) >= sizeof(std::max_align_t) ? sizeof(T) : sizeof(std::max_align_t)
		}
	private:
		void* m_BufferBase;
		void* m_BufferPtr;
		uint32_t m_Count = 0;
		std::unordered_map<EventType, EventHandler> m_Handlers;
	};
}