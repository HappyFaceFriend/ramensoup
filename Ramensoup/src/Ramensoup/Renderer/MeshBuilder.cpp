#include "pch.h"
#include "MeshBuilder.h"

namespace Ramensoup
{
	MeshBuilder::MeshBuilder(size_t vertexCount)
		: m_Verticies(vertexCount), m_Normals(vertexCount), m_TexCoords(vertexCount)
	{
	}

	uint32_t MeshBuilder::AddVertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoord)
	{
		m_Verticies.push_back(position);
		m_Normals.push_back(normal);
		m_TexCoords.push_back(texCoord);

		// TODO: Do this a little more cleaner
		if (m_Verticies.size() != m_Normals.size() && m_Normals.size() != m_TexCoords.size())
		{
			RS_CORE_LOG_WARN("MeshBuilder::AddVertex vertex / normal / texcoord count doesn't match! ");
		}

		return m_Verticies.size() - 1;
	}

	void MeshBuilder::AddTriangle(uint32_t indexA, uint32_t indexB, uint32_t indexC)
	{
		m_Indicies.push_back(indexA);
		m_Indicies.push_back(indexB);
		m_Indicies.push_back(indexC);
	}

	std::shared_ptr<Mesh> MeshBuilder::Build()
	{
		return std::make_shared<Mesh>(m_Verticies.data(), m_Normals.data(), m_TexCoords.data(), m_Indicies.data(), m_Verticies.size(), m_Indicies.size());
	}
}
