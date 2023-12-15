#include "pch.h"
#include "Mesh.h"

namespace Ramensoup
{
	Mesh::Mesh(const glm::vec3* positions, const glm::vec3* normals, const glm::vec2* texCoords, const uint32_t* indicies, size_t vertexCount, size_t indexCount)
		:m_Verticies(vertexCount), m_Indicies(indexCount)
	{
		for (size_t idx = 0; idx < vertexCount; idx++)
			m_Verticies[idx] = { positions[idx], normals[idx], texCoords[idx] };
		for (size_t idx = 0; idx < indexCount; idx++)
			m_Indicies[idx] = indicies[idx];

		m_VertexBuffer = VertexBuffer::Create(m_Verticies.data(), sizeof(Vertex) * m_Verticies.size());
		m_VertexBuffer->SetLayout({
				{ Shader::DataType::Float3}, //position
				{ Shader::DataType::Float3}, //normal
				{ Shader::DataType::Float2} //texcoord
			});
		m_IndexBuffer = IndexBuffer::Create(m_Indicies.data(), m_Indicies.size());
	}

}