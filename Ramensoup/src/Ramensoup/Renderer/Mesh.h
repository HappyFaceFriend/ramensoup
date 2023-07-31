#pragma once

#include <glm/glm.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Ramensoup
{
	class Mesh
	{
	public:
		Mesh(const glm::vec3 const* positions, uint32_t vertexCount, const uint32_t const* indicies, uint32_t indexCount);
		Mesh(const std::vector<glm::vec3>&& positions, const std::vector<uint32_t>&& indicies);

		//TODO : setters
		inline const std::vector<glm::vec3>& GetPositions() const { return m_Positions; }
		inline const std::vector<uint32_t>& GetIndicies() const { return m_Indicies; }

		inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		
	private:
		const std::vector<glm::vec3> m_Positions;
		//TODO : uvs, customs
		const std::vector<uint32_t> m_Indicies;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
}