#include <Ramensoup.h>
#include <Ramensoup/Core/Entrypoint.h>

#include <imgui.h>

#include "Editor/OrthographicCameraController.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flag

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
		
		OrthographicCameraController m_CameraController;
	public:
		TestLayer()
			:m_CameraController(16.0f/9.0f, 5.625)
		{

		}
		virtual void OnAttach() override
		{
			//m_Meshes = MeshLoader::LoadOBJ("assets/models/Toyota Supra MK4 Custom/model/mk5_on_4.obj");
			m_Meshes = MeshLoader::LoadOBJ("assets/models/low-poly-garen_/source/b137609479e34bc3bf215142d91b745b.obj");
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

			for(auto mesh : m_Meshes)
				Renderer::Submit(mesh, m_Material);
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


