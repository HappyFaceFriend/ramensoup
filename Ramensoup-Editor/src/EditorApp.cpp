#include "EditorApp.h"

#include <Ramensoup/Core/Entrypoint.h>
#include "EditorLayer.h"

namespace Ramensoup
{
	EditorApp::EditorApp()
		:Application()
	{
		RS_LOG("Hello Editor!");
		PushLayer(new EditorLayer());
	}


	Application* CreateApplication()
	{
		return new EditorApp();
	}

}