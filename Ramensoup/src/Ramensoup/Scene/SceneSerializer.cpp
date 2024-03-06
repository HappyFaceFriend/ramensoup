#include "pch.h"
#include "SceneSerializer.h"

#include <yaml-cpp/yaml.h>

#include "Entity.h"
#include "Components.h"

#include "Ramensoup/Renderer/MeshLoader.h"

namespace YAML {
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}
		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;
			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};
}

namespace Ramensoup
{
	SceneSerializer::SceneSerializer(const std::shared_ptr<Scene>& scene)
		:m_Scene(scene)
	{
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}
	static void SerializeEntity(YAML::Emitter& out, const Entity& entity)
	{
		out << YAML::BeginMap; //Entity
		// TODO : make guid for entity
		out << YAML::Key << "Entity" << YAML::Value << 123123123;


		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; //Tag
			out << YAML::Key << "Tag" << YAML::Value << entity.GetComponent<TagComponent>().Tag;
			out << YAML::EndMap;	//Tag
		}
		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; //Tag
			auto& transform = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Position" << YAML::Value << transform.Position;
			out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << transform.Scale;
			out << YAML::EndMap;	//Tag
		}
		if (entity.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; //Tag
			auto& camera = entity.GetComponent<CameraComponent>();
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.Projection.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.Projection.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.Projection.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.Projection.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.Projection.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.Projection.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.Projection.GetOrthographicFarClip();
			out << YAML::EndMap;	//Tag
		}
		if (entity.HasComponent<MeshRendererComponent>())
		{
			out << YAML::Key << "MeshRendererComponent";
			out << YAML::BeginMap; //Tag
			auto& meshRenderer = entity.GetComponent<MeshRendererComponent>();
			out << YAML::Key << "MeshFilePath" << YAML::Value << meshRenderer.Mesh->GetFilePath();
			//TODO : Save material
			out << YAML::EndMap;	//Tag
		}

		out << YAML::EndMap; //Entity

	}
	void SceneSerializer::SerializeToText(const std::string& filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled scene";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.each([&](auto entityID)
			{
				Entity entity = { entityID, m_Scene.get() };
				if (!entity)
					return;

				SerializeEntity(out, entity);
			});
		out << YAML::EndSeq << YAML::EndMap;

		std::ofstream fout(filePath);
		fout << out.c_str();
	}
	void SceneSerializer::SerializeToBinary(const std::string& filePath)
	{
		RS_CORE_ASSERT(false, "Not implemented");
	}
	bool SceneSerializer::DeserializeFromText(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;
		
		std::string sceneName = data["Scene"].as<std::string>();
		RS_CORE_LOG("Deserializing scene {0}", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto& entity : entities)
			{
				uint64_t uuid = entity["Entity"].as<uint64_t>();

				std::string name;
				auto tagComponent = entity["TagComponent"];
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();

				Entity deserializedEntity = m_Scene->CreateEntity(name);

				auto transformComponent = entity["TransformComponent"];
				if (transformComponent)
				{
					auto& tc = deserializedEntity.GetComponent<TransformComponent>();
					tc.Position = transformComponent["Position"].as<glm::vec3>();
					tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					tc.Scale = transformComponent["Scale"].as<glm::vec3>();
				}
				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.AddComponent<CameraComponent>();
					cc.Projection.SetProjectionType((CameraProjection::Type)cameraComponent["ProjectionType"].as<int>());
					cc.Projection.SetPerspectiveVerticalFOV(cameraComponent["PerspectiveFOV"].as<float>());
					cc.Projection.SetPerspectiveNearClip(cameraComponent["PerspectiveNear"].as<float>());
					cc.Projection.SetPerspectiveFarClip(cameraComponent["PerspectiveFar"].as<float>());
					cc.Projection.SetOrthographicSize(cameraComponent["OrthographicSize"].as<float>());
					cc.Projection.SetOrthographicNearClip(cameraComponent["OrthographicNear"].as<float>());
					cc.Projection.SetOrthographicFarClip(cameraComponent["OrthographicFar"].as<float>());
				}
				
			}
		}
	}
	bool SceneSerializer::DeserializeFromBinary(const std::string& filePath)
	{
		RS_CORE_ASSERT(false, "Not implemented");
		return false;
	}
}