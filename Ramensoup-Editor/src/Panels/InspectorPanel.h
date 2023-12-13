#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class InspectorPanel
	{
	public:
		InspectorPanel() = default;

		void OnImGuiRender();
			
		void SetEntity(const Entity& entity) noexcept { m_CurrentEntity = entity; }


	private:
		// TODO : Multiple entity editing
		Entity m_CurrentEntity{};

	};
}