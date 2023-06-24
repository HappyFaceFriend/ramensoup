#include "pch.h"
#include "EventQueue.h"

#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Events/WindowEvents.h"

namespace Ramensoup
{

	void EventQueue::Flush(std::function<void(Event&)> handler)
	{
		for (int i = 0; i < m_Queue.size(); i++)
		{
			handler(*m_Queue[i].get());
		}
		m_Queue.clear();
	}
}