#pragma once

#include "Ramensoup/Core/Layer.h"

namespace Ramensoup
{
	class ProfileLayer : public Layer
	{
	public:
		void OnAttach() override {}
		void OnDetach() override {}
		void OnUpdate() override {}
		void OnImGuiUpdate() override;
	};
}