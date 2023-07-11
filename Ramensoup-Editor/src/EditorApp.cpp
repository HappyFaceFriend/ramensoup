#include <Ramensoup.h>

#include <imgui.h>


namespace Ramensoup
{
	class TestLayer : public Layer
	{
	public:
		virtual void OnAttach() override { RS_LOG("OnAttach");}
		virtual void OnDetach() override { RS_LOG("OnDetach");}

		virtual void OnImGuiUpdate() override 
		{
			ImGui::Begin("test window");
			ImGui::Text("Hello world");
			ImGui::End();
			ImGui::Begin("test window2");
			double d = 0;
			ImGui::InputDouble("Val", &d);
			ImGui::End();
		}

		virtual bool HandleEvent(const KeyPressEvent& e) override 
		{
			RS_LOG("KeyPressed {0}", e.KeyCode);
			return true;
		}
		virtual bool HandleEvent(const MouseMoveEvent& e) override
		{
			RS_LOG("MouseMoved {0},{1}", e.X, e.Y);
			return true;
		}
	};
	class EditorApp : public Application
	{
	public:
		EditorApp()
			:Application()
		{
			RS_LOG("Hello Editor!");
			PushLayer(new TestLayer());
		}
	};

	Application* CreateApplication()
	{
		return new EditorApp();
	}
}


