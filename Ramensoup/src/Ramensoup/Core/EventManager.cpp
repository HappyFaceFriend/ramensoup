#include "pch.h"
#include "EventManager.h"

#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Events/WindowEvents.h"

#include "Ramensoup/Core/Logger.h"

#define FLUSH_QUEUE(x) EventQueue<x>::Flush(std::bind(&EventManager::HandleEvent<x>, this, std::placeholders::_1))

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
		//TODO : Change the odrer to match priority
		//TODO : Check if is empty
		//TODO : Cache the functions
		FLUSH_QUEUE(KeyPressEvent);
		FLUSH_QUEUE(KeyReleaseEvent);
		FLUSH_QUEUE(KeyTypeEvent);
		FLUSH_QUEUE(WindowCloseEvent);
		FLUSH_QUEUE(WindowFocusEvent);
		FLUSH_QUEUE(WindowLoseFocusEvent);
		FLUSH_QUEUE(WindowResizeEvent);
		FLUSH_QUEUE(MouseButtonPressEvent);
		FLUSH_QUEUE(MouseButtonReleaseEvent);
		FLUSH_QUEUE(MouseMoveEvent);
		FLUSH_QUEUE(MouseScrollEvent);
	}


}