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
		void HandleEvent(T& event)
		{
			//TODO : Should be backwards
			for (auto& layer : *m_LayerStack)
			{
				if (event.IsHandled)
					break;
				layer->HandleEvent(event);
			}
		}
	private:
		LayerStack* m_LayerStack;
	};

}