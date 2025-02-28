#pragma once

#include <glm/glm.hpp>
#include "Mesh.h"

namespace Ramensoup
{
	class MeshBuilder
	{
	public:
		MeshBuilder() = default;
		MeshBuilder(size_t vertexCount);
		~MeshBuilder() = default;

		MeshBuilder(const MeshBuilder&) = delete;
		MeshBuilder& operator=(const MeshBuilder&) = delete;

		MeshBuilder(MeshBuilder&& other) = default;
		MeshBuilder& operator=(MeshBuilder&& other) = default;

	public:
		// Adds a vertex, returns its index in the vertex buffer.
		uint32_t AddVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoord);
		void AddTriangle(uint32_t indexA, uint32_t indexB, uint32_t indexC);

		[[nodiscard]] std::shared_ptr<Mesh> Build();

	private:
		std::vector<glm::vec3> m_Verticies;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec2> m_TexCoords;
		std::vector<uint32_t> m_Indicies;
	};

}
