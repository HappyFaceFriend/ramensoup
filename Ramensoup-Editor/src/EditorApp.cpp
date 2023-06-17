#include <Ramensoup.h>


namespace Ramensoup
{
	class TestLayer : public Layer
	{
	public:
		virtual void OnAttach() override { Logger::Info("OnAttach");}
		virtual void OnDetach() override { Logger::Info("OnDetach");}
		virtual void OnUpdate() override { Logger::Info("OnUpdate");}

		virtual bool HandleEvent(const KeyPressEvent& event) override 
		{
			Logger::Info("KeyPressed {0}", event.KeyCode);
			return true;
		}
		virtual bool HandleEvent(const MouseMoveEvent& event) override
		{
			Logger::Info("MouseMoved {0},{1}", event.X, event.Y);
			return true;
		}
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


