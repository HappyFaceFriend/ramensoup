#pragma once

#include "Ramensoup/Events/Event.h"

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
		//TODO : To remove EventDispatcher, Layer should implement all kinds of eventHandlers, specific to type.
		//		 As a result, HandleEvent() should dispatch events.
		virtual void HandleEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}