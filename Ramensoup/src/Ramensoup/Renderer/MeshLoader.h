#pragma once

#include "Mesh.h"

#include <assimp/scene.h>           // Output data structure

namespace Ramensoup
{
	class MeshLoader
	{
	public:
		static std::vector<std::shared_ptr<Mesh>> LoadOBJ(const std::string& filePath);

	//private:
		static std::shared_ptr<Mesh> LoadSingleMesh(const aiMesh* meshData);
	};
}