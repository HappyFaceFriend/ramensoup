#include "pch.h"
#include "EventQueue.h"

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

	EventQueue::EventQueue()
	{
		m_BufferBase = new byte[MAX_QUEUE_SIZE_BYTES];
		m_FrontPtr = m_BufferBase;
		m_RearPtr = m_BufferBase;
	}
	EventQueue::~EventQueue()
	{
		delete m_BufferBase;
	}
	Event& EventQueue::Pop()
	{
		RS_CORE_ASSERT(m_FrontPtr < m_RearPtr, "Tried to pop from empty event queue!");

		auto size = *(uint32_t*)m_FrontPtr;
		m_FrontPtr = (char*)m_FrontPtr + sizeof(uint32_t);

		Event& e = *(Event*)m_FrontPtr;
		m_FrontPtr = (char*)m_FrontPtr + size;

		return e;
	}
	void EventQueue::Clear()
	{
		m_FrontPtr = m_BufferBase;
		m_RearPtr = m_BufferBase;
	}
}