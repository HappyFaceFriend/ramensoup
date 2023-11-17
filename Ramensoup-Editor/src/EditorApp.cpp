#include "EditorApp.h"

#include <Ramensoup/Core/Entrypoint.h>

namespace Ramensoup
{
	EditorApp::EditorApp()
		:Application()
	{
		RS_LOG("Hello Editor!");

		m_EditorLayer = std::make_unique<EditorLayer>();

		PushLayer(m_EditorLayer.get());
	}


	Application* CreateApplication()
	{
		return new EditorApp();
	}

}