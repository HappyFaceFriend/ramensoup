#pragma once

#include "Ramensoup/Events/Event.h"
#include "Ramensoup/Events/KeyEvents.h"
#include "Ramensoup/Events/WindowEvents.h"
#include "Ramensoup/Events/MouseEvents.h"

namespace Ramensoup
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}

		inline const std::string& GetName() const { return m_DebugName; }

		virtual bool HandleEvent(const KeyReleaseEvent& event)			{ return false; }
		virtual bool HandleEvent(const KeyPressEvent& event)			{ return false; }
		virtual bool HandleEvent(const KeyTypeEvent& event)				{ return false; }
		virtual bool HandleEvent(const WindowCloseEvent& event)			{ return false; }
		virtual bool HandleEvent(const WindowFocusEvent& event)			{ return false; }
		virtual bool HandleEvent(const WindowLoseFocusEvent& event)		{ return false; }
		virtual bool HandleEvent(const WindowResizeEvent& event)		{ return false; }
		virtual bool HandleEvent(const MouseButtonPressEvent& event)	{ return false; }
		virtual bool HandleEvent(const MouseButtonReleaseEvent& event)	{ return false; }
		virtual bool HandleEvent(const MouseMoveEvent& event)			{ return false; }
		virtual bool HandleEvent(const MouseScrollEvent& event)			{ return false; }

	protected:
		std::string m_DebugName;
	};
}