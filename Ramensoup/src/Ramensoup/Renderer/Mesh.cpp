#include "pch.h"
#include "Mesh.h"

namespace Ramensoup
{
	/*
	Mesh::Mesh(const glm::vec3 const* positions, uint32_t vertexCount, const uint32_t const* indicies, uint32_t indexCount)
		:m_Positions(positions, positions + vertexCount), m_Indicies(indicies, indicies + indexCount)
	{
		m_VertexBuffer = VertexBuffer::Create(positions, sizeof(glm::vec3) * vertexCount);
		m_VertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position" }
			});
		m_IndexBuffer = IndexBuffer::Create(indicies, indexCount);
	}
	Mesh::Mesh(const std::vector<glm::vec3>&& positions, const std::vector<uint32_t>&& indicies)
		:m_Positions(positions), m_Indicies(indicies)
	{
		m_VertexBuffer = VertexBuffer::Create(positions.data(), sizeof(glm::vec3) * positions.size());
		m_VertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position" }
			});
		m_IndexBuffer = IndexBuffer::Create(indicies.data(), indicies.size());
	}*/
	Mesh::Mesh(const glm::vec3* positions, const glm::vec3* normals, const glm::vec2* texCoords, const uint32_t* indicies, uint32_t vertexCount, uint32_t indexCount)
		:m_Verticies(vertexCount), m_Indicies(indexCount)
	{
		for (int idx = 0; idx < vertexCount; idx++)
			m_Verticies[idx] = { positions[idx], normals[idx], texCoords[idx] };
		for (int idx = 0; idx < indexCount; idx++)
			m_Indicies[idx] = indicies[idx];

		m_VertexBuffer = VertexBuffer::Create(m_Verticies.data(), sizeof(Vertex) * m_Verticies.size());
		m_VertexBuffer->SetLayout({
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float3, "a_Normal" },
				{ ShaderDataType::Float2, "a_TexCoord" }
			});
		m_IndexBuffer = IndexBuffer::Create(m_Indicies.data(), m_Indicies.size());
	}

}