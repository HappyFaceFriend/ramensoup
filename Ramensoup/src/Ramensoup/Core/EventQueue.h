#pragma once

#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Core/LayerStack.h"

#include <any>

namespace Ramensoup
{
	/*
		This EventQueue stores different types of events in a single queue.
		It is achived by saving the event's size and type as a header of each event.
	*/
	class EventQueue
	{
	public:
	public:
		EventQueue();
		~EventQueue();

		inline bool IsEmpty() const { return m_FrontPtr >= m_RearPtr; }
		Event& Pop();
		void Clear();

		template <typename T>
		void Push(const T& e)
		{
			//Store event size
			*(uint32_t*)m_RearPtr = PaddedSizeof<T>();
			m_RearPtr = (char*)m_RearPtr + sizeof(uint32_t);
			//Store event type
			*(EventType*)m_RearPtr = T::GetStaticType();
			m_RearPtr = (char*)m_RearPtr + sizeof(EventType);
			//Store actual event
			//*(T*)m_RearPtr = e;
			memcpy(m_RearPtr, &e, sizeof(T));
			m_RearPtr = (char*)m_RearPtr + PaddedSizeof<T>();
		}
	private:

		template<typename T>
		constexpr static uint32_t PaddedSizeof()
		{
			return (sizeof(T) + sizeof(std::max_align_t) - 1) % sizeof(std::max_align_t) * sizeof(std::max_align_t);
		}
	private:
		void* m_BufferBase;
		void* m_FrontPtr;
		void* m_RearPtr;
	};
}