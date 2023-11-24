#include "pch.h"
#include "MeshLoader.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/postprocess.h>     // Post processing flag

namespace Ramensoup
{
	std::vector<std::shared_ptr<Mesh>> MeshLoader::LoadOBJ(const std::string& filePath) //"assets/models/Toyota Supra MK4 Custom/model/mk5_on_4.obj"
	{
		std::vector<std::shared_ptr<Mesh>> meshes;

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			RS_LOG_ERROR("Failed loading {0}: {0}", filePath, importer.GetErrorString());
			return meshes;
		}
		
		for (int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
		{
			auto mesh = LoadSingleMesh(scene->mMeshes[meshIndex]);
			meshes.push_back(mesh);
		}


		return meshes;
	}
	std::shared_ptr<Mesh> MeshLoader::LoadSingleMesh(const aiMesh* meshData)
	{
		uint32_t vertexCount = meshData->mNumVertices;


		//assimp Texcoords is 3d
		// TODO : This is currently loading only the first texture's uv
		std::vector<glm::vec2> texCoords(vertexCount);
		uint32_t textureID = 0;
		for (int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
		{
			if (meshData->HasTextureCoords(textureID))
				texCoords[vertexIndex] = { meshData->mTextureCoords[textureID][vertexIndex].x, meshData->mTextureCoords[textureID][vertexIndex].y };
			else
				texCoords[vertexIndex] = { 0,0 };
		}
		
		//assimp indicies is stored as triangles(faces)
		std::vector<uint32_t> indicies(meshData->mNumFaces * 3);
		for (int faceIndex = 0; faceIndex < meshData->mNumFaces; faceIndex++)
		{
			for (int i = 0; i < 3; i++)
				indicies[faceIndex * 3 + i] = meshData->mFaces[faceIndex].mIndices[i];
		}

		// TODO : This can be optimized by making a MeshBuilder, letting texcoords & indicies be swapped or directly initialized
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(reinterpret_cast<glm::vec3*>(meshData->mVertices),
															reinterpret_cast<glm::vec3*>(meshData->mNormals),
															texCoords.data(), 
															indicies.data(),
															vertexCount, meshData->mNumFaces * 3);
		return mesh;
	}
}