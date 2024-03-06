#include "pch.h"
#include "SceneSerializer.h"

#include <yaml-cpp/yaml.h>

#include "Entity.h"
#include "Components.h"



namespace Ramensoup
{
	SceneSerializer::SceneSerializer(const std::shared_ptr<Scene>& scene)
		:m_Scene(scene)
	{
	}
	static void SerializeEntity(YAML::Emitter& out, const Entity& entity)
	{
		out << YAML::BeginMap; //Entity
		// TODO : make guid for entity
		out << YAML::Key << "Entity" << YAML::Value << "123123";


		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; //Tag
			out << YAML::Key << "Tag" << YAML::Value << entity.GetComponent<TagComponent>().Tag;
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
	bool SceneSerializer::DeserializeToText(const std::string& filePath)
	{
		return false;
	}
	bool SceneSerializer::DeserializeToBinary(const std::string& filePath)
	{
		RS_CORE_ASSERT(false, "Not implemented");
		return false;
	}
}