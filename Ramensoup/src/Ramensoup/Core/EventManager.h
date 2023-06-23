#pragma once

#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Core/LayerStack.h"
#include "Ramensoup/Core/EventQueue.h"
namespace Ramensoup
{
	class EventManager
	{
	public:
		EventManager(LayerStack* layerStack);
		~EventManager();

		template <typename T>
		void Push(T&& e)
		{
			m_EventQueue.Push<T>(std::forward(e));
		}
		void Flush();

	private:
		template <typename T>
		void HandleEvent(Event& e)
		{
			for (auto iter = m_LayerStack->end(); iter != m_LayerStack->begin(); )
			{
				iter--;
				if (e.IsHandled)
					break;
				e.IsHandled = (*iter)->HandleEvent((T)e);
			}
		}
	private:
		EventQueue m_EventQueue;
		LayerStack* m_LayerStack;
	};

}