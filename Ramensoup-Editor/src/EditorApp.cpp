#include <Ramensoup.h>
#include <Ramensoup/Core/Entrypoint.h>

#include <imgui.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Editor/PerspectiveCameraController.h"

namespace Ramensoup
{
	class TestLayer : public Layer
	{
	private:
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;

		std::vector<std::shared_ptr<Mesh>> m_Meshes;
		std::shared_ptr<Material> m_Material;
		std::shared_ptr<Texture2D> m_Texture;
		glm::mat4 m_ModelTransform = glm::mat4(1.0f);

		PerspectiveCameraController m_CameraController;
	public:
		TestLayer()
			:m_CameraController(16.0f/9.0f, glm::radians(60.0f), 0.1f, 100)
		{
			m_ModelTransform = glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 0));
		}
		virtual void OnAttach() override
		{
			//m_Meshes = MeshLoader::LoadOBJ("assets/models/Toyota Supra MK4 Custom/model/mk5_on_4.obj");
			m_Meshes = MeshLoader::LoadOBJ("assets/models/low-poly-garen_/source/b137609479e34bc3bf215142d91b745b.obj");
			m_Shader = Shader::Create("assets/shaders/Lit.glsl");

			m_Material = std::shared_ptr<Material>(new Material("Lit", m_Shader));
			m_Material->GetShader()->Bind();
			//m_Material->GetShader()->SetUniformFloat4("u_Color", glm::vec4(0.8f, 0.2f, 0.3f, 1.0f));

			m_Texture = Texture2D::Create("assets/models/low-poly-garen_/textures/garen_tex.jpg");
			m_Texture->Bind();
			Renderer::SetClearColor(glm::vec4(0.2, 0.2, 0.2, 1));
		}
		virtual void OnDetach() override { RS_LOG("OnDetach");}
		virtual void OnUpdate() override
		{
			m_CameraController.OnUpdate();

			Renderer::BeginScene(m_CameraController.GetCamera().GetProjectionMatrix(), m_CameraController.GetCamera().GetViewMatrix());

			for(auto mesh : m_Meshes)
				Renderer::Submit(mesh, m_Material, m_ModelTransform);
			Renderer::EndScene();
		}
		virtual void OnImGuiUpdate() override 
		{
			ImGui::Begin("test window");
			ImGui::Text("Frame time: %fms", Time::GetDeltaTime() * 1000);
			ImGui::Text("FPS: %f", 1 / Time::GetDeltaTime());
			ImGui::Spacing();
			ImGui::Text("Draw Calls: %d", Renderer::GetStatistics().DrawCallCount);
			ImGui::Text("Indicies: %d", Renderer::GetStatistics().TotalIndexCount);
			ImGui::End();
			ImGui::Begin("test window2");
			glm::vec3 position = m_CameraController.GetPosition();
			ImGui::DragFloat3("Camera Position", glm::value_ptr(position));
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


