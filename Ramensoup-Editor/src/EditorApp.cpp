#include <Ramensoup.h>


namespace Ramensoup
{
	class TestLayer : public Layer
	{
	public:
		virtual void OnAttach() override { Logger::Info("OnAttach");}
		virtual void OnDetach() override { Logger::Info("OnDetach");}

		virtual bool HandleEvent(const KeyPressEvent& e) override 
		{
			Logger::Info("KeyPressed {0}", e.KeyCode);
			return true;
		}
		virtual bool HandleEvent(const MouseMoveEvent& e) override
		{
			Logger::Info("MouseMoved {0},{1}", e.X, e.Y);
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


