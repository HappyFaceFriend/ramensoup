#pragma once

#include "Mesh.h"

#include <assimp/scene.h>           // Output data structure

namespace Ramensoup
{
	class MeshLoader
	{
	public:
		MeshLoader() = delete;

	public:
		[[nodiscard]] static std::shared_ptr<Mesh> LoadOBJ(const std::string& filePath);
		[[nodiscard]] static std::shared_ptr<Mesh> LoadSingleMesh(const aiMesh* meshData);

	};
}