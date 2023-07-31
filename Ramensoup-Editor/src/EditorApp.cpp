#include <Ramensoup.h>
#include <Ramensoup/Core/Entrypoint.h>

#include <imgui.h>

#include "Editor/OrthographicCameraController.h"

namespace Ramensoup
{
	class TestLayer : public Layer
	{
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;
		
		OrthographicCameraController m_CameraController;
	public:
		TestLayer()
			:m_CameraController(16.0f/9.0f, 5.625)
		{

		}
		virtual void OnAttach() override
		{

			glm::vec3 verticies[3] = {
		{ -0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f}
			};

			uint32_t indicies[3] = {
				0,1,2
			};
			/*
			m_VertexBuffer = VertexBuffer::Create(verticies, sizeof(verticies));
			m_VertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position" }
				});


			m_IndexBuffer = IndexBuffer::Create(indicies, 3);
			*/
			m_Mesh = std::shared_ptr<Mesh>(new Mesh(verticies, 3, indicies, 3));
			
			
			m_Shader = Shader::Create("assets/shaders/FlatColor.glsl");

			m_Material = std::shared_ptr<Material>(new Material("FlatColor", m_Shader));
			m_Material->GetShader()->Bind();
			m_Material->GetShader()->SetUniformFloat4("u_Color", glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));

		}
		virtual void OnDetach() override { RS_LOG("OnDetach");}
		virtual void OnUpdate() override
		{
			m_CameraController.OnUpdate();

			Renderer::BeginScene(m_CameraController.GetCamera().GetProjectionMatrix(), m_CameraController.GetCamera().GetViewMatrix());

			Renderer::Submit(m_Mesh, m_Material);
			//Renderer::DrawIndexed(m_VertexBuffer, m_IndexBuffer);
			Renderer::EndScene();
		}
		virtual void OnImGuiUpdate() override 
		{
			ImGui::Begin("test window");
			ImGui::Text("Frame time: %fms", Time::GetDeltaTime() * 1000);
			ImGui::Text("FPS: %f", 1 / Time::GetDeltaTime());
			ImGui::End();
			ImGui::Begin("test window2");
			double d = 0;
			ImGui::InputDouble("Val", &d);
			ImGui::End();
		}

		virtual bool HandleEvent(const KeyPressEvent& e) override 
		{
			//RS_LOG("KeyPressed {0}", e.KeyCode);
			return true;
		}
		virtual bool HandleEvent(const MouseMoveEvent& e) override
		{
			//RS_LOG("MouseMoved {0},{1}", e.X, e.Y);
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


