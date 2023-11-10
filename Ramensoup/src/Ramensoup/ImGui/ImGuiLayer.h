#pragma once

#include "Ramensoup/Core/Layer.h"
#include "Ramensoup/Core/Window.h"

namespace Ramensoup
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(Window* window);
		virtual ~ImGuiLayer() override;

		virtual bool HandleEvent(const KeyPressEvent& e) override;

		inline void SetBlockEvents(bool block) { m_BlockEvent = block; }
	private:
		bool m_BlockEvent = false;
	};
}