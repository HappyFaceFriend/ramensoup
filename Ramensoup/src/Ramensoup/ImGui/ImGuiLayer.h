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
	};
}