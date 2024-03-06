#pragma once
#include "Scene.h"


namespace Ramensoup
{
	class SceneSerializer
	{
	public:
		SceneSerializer(const std::shared_ptr<Scene>& scene);
		
		void SerializeToText(const std::string& filePath);
		void SerializeToBinary(const std::string& filePath);
		bool DeserializeFromText(const std::string& filePath);
		bool DeserializeFromBinary(const std::string& filePath);

	private:
		std::shared_ptr<Scene> m_Scene;
	};
}