#include <Ramensoup.h>


namespace Ramensoup
{
	class TestLayer : public Layer
	{
	public:
		virtual void OnAttach() override { Logger::Info("OnAttach");}
		virtual void OnDetach() override { Logger::Info("OnDetach");}
		virtual void OnUpdate() override { Logger::Info("OnUpdate");}
		virtual void HandleEvent(Event& event) override {
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<KeyPressEvent>(std::bind(&TestLayer::KeyPressEventHandler, this, std::placeholders::_1));
			dispatcher.Dispatch<MouseMoveEvent>(std::bind(&TestLayer::MouseMoveHandler, this, std::placeholders::_1));
		}
		bool KeyPressEventHandler(const KeyPressEvent& event)
		{
			Logger::Info("KeyPressed {0}", event.KeyCode);
			return true;
		}
		bool MouseMoveHandler(const MouseMoveEvent& event)
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


