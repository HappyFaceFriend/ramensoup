#pragma once

#include "Ramensoup/Core/Layer.h"

namespace Ramensoup
{
	class ProfileLayer : public Layer
	{
	public:
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiUpdate() override;
	};
}