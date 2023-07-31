#pragma once

#include <glm/glm.hpp>

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
		
	private:
		const std::vector<glm::vec3> m_Positions;
		//TODO : uvs, customs
		const std::vector<uint32_t> m_Indicies;

	};
}