#include "pch.h"
#include "EventQueue.h"

#include "Ramensoup/Core/Logger.h"
#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Events/WindowEvents.h"

#define DISPATCH(EventT)	case EventType::##EventT: \
								HandleEvent<##EventT##Event>((##EventT##Event*)ptr, layerStack); \
								ptr = (char*)ptr + PaddedSizeof<##EventT##Event>(); \
								break

namespace Ramensoup
{
	static constexpr uint32_t MAX_QUEUE_SIZE_BYTES = 1000;
	using byte = uint8_t;

	EventQueue* EventQueue::s_Instance = nullptr;
	static EventQueue instance;

	EventQueue::EventQueue()
	{
		s_Instance = this;
		m_BufferBase = new byte[MAX_QUEUE_SIZE_BYTES];
		m_BufferPtr = m_BufferBase;
	}
	EventQueue::~EventQueue()
	{
		delete m_BufferBase;
	}
	void EventQueue::Flush(LayerStack& layerStack)
	{
		void* ptr = m_BufferBase;
		while (ptr < m_BufferPtr)
		{
			EventType eventType = *(EventType*)ptr;
			ptr = (char*)ptr + sizeof(EventType*);

			switch (eventType)
			{
			DISPATCH(KeyPress);
			DISPATCH(KeyRelease);
			DISPATCH(KeyType);
			DISPATCH(WindowClose);
			DISPATCH(WindowFocus);
			DISPATCH(WindowLoseFocus);
			DISPATCH(WindowResize);
			DISPATCH(MouseButtonPress);
			DISPATCH(MouseButtonRelease);
			DISPATCH(MouseMove);
			DISPATCH(MouseScroll);
			default:
				RS_CORE_ASSERT(false, "Unknown event!");
				break;
			}
		}
		m_BufferPtr = m_BufferBase;
		m_Count = 0;
	}
}