#pragma once

#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Core/LayerStack.h"

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

		template <typename T>
		void Push(T&& e)
		{
			//Store event type
			*(EventType*)m_BufferPtr = T::GetStaticType();
			m_BufferPtr = (char*)m_BufferPtr + sizeof(EventType*);
			//Store actual event
			*(T*)m_BufferPtr = std::move(e);
			m_BufferPtr = (char*)m_BufferPtr + PaddedSizeof<T>();
			m_Count++;
		}

		void Flush(LayerStack& layerStack);

		template <typename T>
		static void HandleEvent(Event* e, LayerStack& layerStack)
		{
			layerStack.HandleEvent<T>(*(T*)e);
		}
		
		static EventQueue& Get() { return *s_Instance; }

	private:

		template<typename T>
		static uint32_t PaddedSizeof()
		{
			return sizeof(T) >= sizeof(std::max_align_t) ? sizeof(T) : sizeof(std::max_align_t);
		}
	private:
		void* m_BufferBase;
		void* m_BufferPtr;
		uint32_t m_Count = 0;
	private:
		static EventQueue* s_Instance;
	};
}