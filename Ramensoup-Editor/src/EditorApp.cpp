#include "EditorApp.h"

#include <Ramensoup/Core/Entrypoint.h>

namespace Ramensoup
{
	EditorApp::EditorApp()
	{
		RS_LOG("Hello Editor!");

		m_EditorLayer = std::make_shared<EditorLayer>();

		PushLayer(m_EditorLayer);
	}


	Application* CreateApplication()
	{
		return new EditorApp();
	}

}