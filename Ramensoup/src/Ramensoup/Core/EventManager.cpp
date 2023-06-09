#include "pch.h"
#include "EventManager.h"

#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Events/WindowEvents.h"

#include "Ramensoup/Core/Logger.h"

namespace Ramensoup
{

	EventManager::EventManager(LayerStack* layerStack)
		: m_LayerStack(layerStack)
	{
	}

	EventManager::~EventManager()
	{
	}
	void EventManager::Flush()
	{
		std::function<void(Event&)> eventHandler = std::bind(&EventManager::HandleEvent, this, std::placeholders::_1);
		EventQueue<KeyPressEvent>::Flush(eventHandler);
		EventQueue<KeyReleaseEvent>::Flush(eventHandler);
		EventQueue<MouseMoveEvent>::Flush(eventHandler);
	}

	void EventManager::HandleEvent(Event& event)
	{
		for (auto& layer : *m_LayerStack)
		{
			if (event.IsHandled)
				break;
			layer->HandleEvent(event);
		}
	}

}