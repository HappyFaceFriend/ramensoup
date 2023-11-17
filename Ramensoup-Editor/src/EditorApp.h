#pragma once
#include <Ramensoup.h>

#include "EditorLayer.h"

namespace Ramensoup
{
	class EditorApp : public Application
	{
	public:
		EditorApp();

	private:
		std::unique_ptr<EditorLayer> m_EditorLayer;

	};
}