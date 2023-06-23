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

		using EventHandler = std::function<void(Event*, const LayerStack&)>;


		template <typename T>
		struct HandlerSetter
		{
			HandlerSetter() { EventQueue::Get().m_Handlers[T::GetStaticType()] =  EventQueue::HandleEvent<T>; }
		};

		template <typename T>
		void Push(T&& e)
		{
			static HandlerSetter<T> set;
			//Store size of the event
			*(EventType*)m_BufferPtr = T::GetStaticType();
			m_BufferPtr = (char*)m_BufferPtr + sizeof(EventType*);
			//Store actual event
			*(T*)m_BufferPtr = std::move(e);		//TODO : Test if copy constructor is called
			m_BufferPtr = (char*)m_BufferPtr + PaddedSizeof<T>();
			m_Count++;
		}

		void Flush(const LayerStack& layerStack);

		template <typename T>
		static void HandleEvent(Event* e, const LayerStack& layerStack)
		{
			for (auto iter = layerStack.end(); iter != layerStack.begin(); )
			{
				iter--;
				if (e->IsHandled)
					break;
				e->IsHandled = (*iter)->HandleEvent(*(T*)e);
			}
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
		std::unordered_map<EventType, EventHandler> m_Handlers;
	private:
		static EventQueue* s_Instance;
	};
}