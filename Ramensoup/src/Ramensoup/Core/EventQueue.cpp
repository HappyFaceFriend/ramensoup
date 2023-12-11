#include "pch.h"
#include "EventQueue.h"

#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Events/WindowEvents.h"

namespace Ramensoup
{

	EventQueue::EventQueue()
		:m_BufferBase(new byte[MAX_QUEUE_SIZE_BYTES]),
		m_FrontPtr(m_BufferBase.get()),
		m_RearPtr(m_BufferBase.get())
	{
	}
	Event& EventQueue::Pop()
	{
		RS_CORE_ASSERT(m_FrontPtr < m_RearPtr, "Tried to pop from empty event queue!");

		uint32_t size = *reinterpret_cast<uint32_t*>(m_FrontPtr);
		m_FrontPtr = m_FrontPtr + sizeof(uint32_t);

		Event* e = reinterpret_cast<Event*>(m_FrontPtr);
		m_FrontPtr = m_FrontPtr + size;

		return *e;
	}
	void EventQueue::Clear()
	{
		m_FrontPtr = m_BufferBase.get();
		m_RearPtr = m_BufferBase.get();
	}
}