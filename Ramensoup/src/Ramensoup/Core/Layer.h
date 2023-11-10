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

		virtual bool HandleEvent(const Event& e) { return false; }

	protected:
		std::string m_DebugName;
	};
}