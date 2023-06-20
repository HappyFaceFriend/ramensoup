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

		void Flush();

	private:
		template <typename T>
		void HandleEvent(T& e)
		{
			//TODO : Should be backwards
			for (auto iter = m_LayerStack->end(); iter != m_LayerStack->begin(); )
			{
				iter--;
				if (e.IsHandled)
					break;
				(*iter)->HandleEvent(e);
			}
		}
	private:
		LayerStack* m_LayerStack;
	};

}