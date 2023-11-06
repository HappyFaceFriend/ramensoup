#include <pch.h>
#include "MeshLoader.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/postprocess.h>     // Post processing flag

namespace Ramensoup
{
	std::shared_ptr<Mesh> MeshLoader::LoadOBJ(const std::string& filePath) //"assets/models/Toyota Supra MK4 Custom/model/mk5_on_4.obj"
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			RS_LOG_ERROR("Failed loading {0}: {0}", filePath, importer.GetErrorString());
			return nullptr;
		}
		
		auto mesh = LoadSingleMesh(scene->mMeshes[0]);

		return mesh;
	}
	std::shared_ptr<Mesh> MeshLoader::LoadSingleMesh(const aiMesh* meshData)
	{
		uint32_t vertexCount = meshData->mNumVertices;


		//assimp Texcoords is 3d
		// TODO : This is currently loading only the first texture's uv
		std::vector<glm::vec2> texCoords(vertexCount);
		for(int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
			texCoords[vertexIndex] = { meshData->mTextureCoords[0][vertexIndex].x, meshData->mTextureCoords[0][vertexIndex].y };
		
		//assimp indicies is stored as triangles(faces)
		std::vector<uint32_t> indicies(meshData->mNumFaces * 3);
		for (int faceIndex = 0; faceIndex < meshData->mNumFaces; faceIndex++)
		{
			for (int i = 0; i < 3; i++)
				indicies[faceIndex * 3 + i] = meshData->mFaces[faceIndex].mIndices[i];
		}

		// TODO : This can be optimized by making a MeshBuilder, letting texcoords & indicies be swapped or directly initialized
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>((glm::vec3*)meshData->mVertices, (glm::vec3*)meshData->mNormals, texCoords.data(), indicies.data(),
																vertexCount, meshData->mNumFaces * 3);
		return mesh;
	}
}