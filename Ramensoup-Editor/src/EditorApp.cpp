#include <Ramensoup.h>


namespace Ramensoup
{
	class TestLayer : public Layer
	{
		virtual void OnAttach() override { Logger::Info("OnAttach");}
		virtual void OnDetach() override { Logger::Info("OnDetach");}
		virtual void OnUpdate() override { Logger::Info("OnUpdate");}
		virtual bool HandleEvent(const Event& event) { Logger::Info("{0}", event.Name()); return true; }
	};
	class EditorApp : public Application
	{
	public:
		EditorApp()
			:Application()
		{
			Logger::Info("Hello Editor!");
			PushLayer(new TestLayer());
		}
	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}


