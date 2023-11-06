#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Ramensoup
{
	class Mesh
	{
	public:
		//TODO : default constructor
		//Mesh(const glm::vec3 const* positions, uint32_t vertexCount, const uint32_t const* indicies, uint32_t indexCount);
		//Mesh(const std::vector<glm::vec3>&& positions, const std::vector<uint32_t>&& indicies);
	public:
		Mesh(const glm::vec3* positions, const glm::vec3* normals, const glm::vec2* texCoords, const uint32_t* indicies, uint32_t vertexCount, uint32_t indexCount);

	public:

		//TODO : Unity style setters
		/*inline const std::vector<glm::vec3>& GetPositions() const { return m_Positions; }
		inline const std::vector<glm::vec3>& GetNormals() const { return m_Normals; }
		inline const std::vector<glm::vec2>& GetTexCoords() const { return m_TexCoords; }
		inline const std::vector<uint32_t>& GetIndicies() const { return m_Indicies; }*/

		inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		
	private:
		//TODO : uvs, customs
		/*
		std::vector<glm::vec3> m_Positions;
		std::vector<glm::vec3> m_Normals;
		std::vector<glm::vec2> m_TexCoords;
		std::vector<uint32_t> m_Indicies;
		*/
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoord;
		};
		std::vector<Vertex> m_Verticies;
		std::vector<uint32_t> m_Indicies;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
}