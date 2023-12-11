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
		[[nodiscard]] Layer(const zstring_view& name =  "Layer" );
		virtual ~Layer() = default;

		Layer(const Layer&) = delete;
		Layer(Layer&&) = delete;
		Layer& operator=(const Layer&) = delete;
		Layer& operator=(Layer&&) = delete;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiUpdate() {}

		virtual bool HandleEvent(const Event& e) { return false; }

		[[nodiscard]] inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}