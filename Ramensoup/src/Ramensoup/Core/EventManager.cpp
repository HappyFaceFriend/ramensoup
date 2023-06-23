#include "pch.h"
#include "EventManager.h"

#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/MouseEvents.h"
#include "Ramensoup/Events/WindowEvents.h"

#include "Ramensoup/Core/Logger.h"

#define SET_HANDLER(T) m_EventQueue.SetHandler<T>(std::bind(&EventManager::HandleEvent<T>, this, std::placeholders::_1));

namespace Ramensoup
{

	EventManager::EventManager(LayerStack* layerStack)
		: m_LayerStack(layerStack)
	{
		SET_HANDLER(KeyPressEvent);
		SET_HANDLER(KeyReleaseEvent);
		SET_HANDLER(KeyTypeEvent);
		SET_HANDLER(WindowCloseEvent);
		SET_HANDLER(WindowFocusEvent);
		SET_HANDLER(WindowLoseFocusEvent);
		SET_HANDLER(WindowResizeEvent);
		SET_HANDLER(MouseButtonPressEvent);
		SET_HANDLER(MouseButtonReleaseEvent);
		SET_HANDLER(MouseMoveEvent);
		SET_HANDLER(MouseScrollEvent);
	}

	EventManager::~EventManager()
	{
	}


	void EventManager::Flush()
	{
		m_EventQueue.Flush();
	}


}