#include <Ramensoup.h>

#include <imgui.h>


namespace Ramensoup
{
	class TestLayer : public Layer
	{
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;
		
	public:
		virtual void OnAttach() override
		{
			float verticies[3 * 3] = {
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f
			};
			m_VertexBuffer = VertexBuffer::Create(verticies, sizeof(verticies));
			m_VertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "position" }
			});

			
			uint32_t indicies[6] = {
				0,1,2
			};
			m_IndexBuffer = IndexBuffer::Create(indicies, 3);

			m_Shader = Shader::Create("assets/shaders/FlatColor.glsl");

		}
		virtual void OnDetach() override { RS_LOG("OnDetach");}
		virtual void OnUpdate() override
		{
			m_Shader->Bind();
			m_Shader->SetUniformFloat4("u_Color", glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));
			Renderer::DrawIndexed(m_VertexBuffer, m_IndexBuffer);
		}
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


