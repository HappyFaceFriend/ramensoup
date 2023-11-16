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

		virtual bool HandleEvent(const Event& e) override;

		inline void SetBlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = false;
	};
}