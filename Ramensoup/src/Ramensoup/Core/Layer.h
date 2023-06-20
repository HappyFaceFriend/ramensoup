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
		virtual void OnImGuiUpdate() {}

		inline const std::string& GetName() const { return m_DebugName; }

		virtual bool HandleEvent(const KeyReleaseEvent& e)			{ return false; }
		virtual bool HandleEvent(const KeyPressEvent& e)			{ return false; }
		virtual bool HandleEvent(const KeyTypeEvent& e)				{ return false; }
		virtual bool HandleEvent(const WindowCloseEvent& e)			{ return false; }
		virtual bool HandleEvent(const WindowFocusEvent& e)			{ return false; }
		virtual bool HandleEvent(const WindowLoseFocusEvent& e)		{ return false; }
		virtual bool HandleEvent(const WindowResizeEvent& e)		{ return false; }
		virtual bool HandleEvent(const MouseButtonPressEvent& e)	{ return false; }
		virtual bool HandleEvent(const MouseButtonReleaseEvent& e)	{ return false; }
		virtual bool HandleEvent(const MouseMoveEvent& e)			{ return false; }
		virtual bool HandleEvent(const MouseScrollEvent& e)			{ return false; }

	protected:
		std::string m_DebugName;
	};
}