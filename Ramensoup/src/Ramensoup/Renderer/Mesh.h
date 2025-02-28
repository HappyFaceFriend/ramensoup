#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>

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
		Mesh(const glm::vec3* positions, const glm::vec3* normals, const glm::vec2* texCoords, const uint32_t* indicies, size_t vertexCount, size_t indexCount, const zstring_view& name);
		//TODO : default constructor

	public:
		[[nodiscard]] const std::vector<Vertex>& GetVerticies() const { return m_Verticies; }
		[[nodiscard]] const std::vector<uint32_t>& GetIndicies() const { return m_Indicies; }

		[[nodiscard]] const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		[[nodiscard]] const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		[[nodiscard]] const std::string& GetName() const { return m_Name; }
		// TEMP
		void SetFilePath(const zstring_view& filePath) { m_FilePath = filePath; }
		[[nodiscard]] const std::string& GetFilePath() const { return m_FilePath; }
		
	private:
		std::string m_Name;
		std::string m_FilePath;
		std::vector<Vertex> m_Verticies;
		std::vector<uint32_t> m_Indicies;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}