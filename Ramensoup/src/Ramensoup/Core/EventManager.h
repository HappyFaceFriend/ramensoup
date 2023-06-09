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
		void HandleEvent(Event& event);
	private:
		std::vector<std::unique_ptr<Event>> m_Events;

		LayerStack* m_LayerStack;
	};

}