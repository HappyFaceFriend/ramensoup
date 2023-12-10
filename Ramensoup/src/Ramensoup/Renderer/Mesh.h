#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Ramensoup
{
	class Mesh
	{
	public:
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoord;
		};
	public:
		Mesh(const glm::vec3* positions, const glm::vec3* normals, const glm::vec2* texCoords, const uint32_t* indicies, size_t vertexCount, size_t indexCount);
		//TODO : default constructor

	public:

		[[nodiscard]] inline const std::vector<Vertex>& GetVerticies() const { return m_Verticies; }
		[[nodiscard]] inline const std::vector<uint32_t>& GetIndicies() const { return m_Indicies; }

		[[nodiscard]] inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		[[nodiscard]] inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		
	private:
		std::vector<Vertex> m_Verticies;
		std::vector<uint32_t> m_Indicies;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
}