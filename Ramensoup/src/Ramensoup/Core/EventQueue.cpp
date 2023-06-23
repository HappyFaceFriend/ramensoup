#include "pch.h"
#include "EventQueue.h"

#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Events/WindowEvents.h"

#define DISPATCH(EventT)	case EventType::##EventT: \
								m_Handlers[EventType::##EventT](*(##EventT##Event*)ptr); \
								ptr = (char*)ptr + PaddedSizeof<KeyPressEvent>(); \
								break

namespace Ramensoup
{
	static constexpr uint32_t MAX_QUEUE_SIZE_BYTES = 100;
	using byte = uint8_t;

	EventQueue::EventQueue()
	{
		m_BufferBase = new byte[MAX_QUEUE_SIZE_BYTES];
		m_BufferPtr = m_BufferBase;
	}
	EventQueue::~EventQueue()
	{
		delete m_BufferBase;
	}
	void EventQueue::Flush()
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
				//TODO : Assert here
			}
		}
	}
}