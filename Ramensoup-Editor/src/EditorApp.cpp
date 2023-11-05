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

			DoTheImportThing("assets/models/");
		}
		bool DoTheImportThing(const std::string& pFile) {
			// Create an instance of the Importer class
			Assimp::Importer importer;

			// And have it read the given file with some example postprocessing
			// Usually - if speed is not the most important aspect for you - you'll
			// probably to request more postprocessing than we do in this example.
			const aiScene* scene = importer.ReadFile(pFile,
				aiProcess_CalcTangentSpace |
				aiProcess_Triangulate |
				aiProcess_JoinIdenticalVertices |
				aiProcess_SortByPType);

			// If the import failed, report it
			if (nullptr == scene) {
				//DoTheErrorLogging(importer.GetErrorString());
				return false;
			}

			
			// Now we can access the file's contents.
			//DoTheSceneProcessing(scene);

			// We're done. Everything will be cleaned up by the importer destructor
			return true;
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


