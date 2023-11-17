#include "EditorApp.h"

#include <Ramensoup/Core/Entrypoint.h>

namespace Ramensoup
{
	EditorApp::EditorApp()
		:Application()
	{
		RS_LOG("Hello Editor!");

		m_EditorLayer = std::make_unique<EditorLayer>();
		m_ProfileLayer = std::make_unique<ProfileLayer>();

		PushLayer(m_EditorLayer.get());
		PushLayer(m_ProfileLayer.get());
	}


	Application* CreateApplication()
	{
		return new EditorApp();
	}

}