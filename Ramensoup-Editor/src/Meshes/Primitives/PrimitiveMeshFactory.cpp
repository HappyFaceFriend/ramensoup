#include "PrimitiveMeshFactory.h"

#include "Ramensoup/Renderer/MeshBuilder.h"

namespace Ramensoup
{
	std::map<PrimitiveMeshType, std::shared_ptr<Mesh>> PrimitiveMeshFactory::m_Meshes{};

	static void Triangulate(uint32_t detailLevel, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, MeshBuilder& meshBuilder);

	std::shared_ptr<Mesh> PrimitiveMeshFactory::Create(PrimitiveMeshType meshType)
	{
		Mesh newMesh = *PrimitiveMeshFactory::CreateOrGet(meshType).get();
		return std::make_shared<Mesh>(newMesh);
	}

	std::shared_ptr<Mesh> PrimitiveMeshFactory::CreateOrGet(PrimitiveMeshType meshType)
	{
		if (m_Meshes.find(meshType) == m_Meshes.end())
		{
			GenerateSphere();
		}
		return m_Meshes[meshType];
	}

	void PrimitiveMeshFactory::GenerateSphere(int detailLevel/* =DefaultSphereDetailLevel */)
	{
		MeshBuilder meshBuilder;

		// Start with octahedron
		static glm::vec3 v[6] = {
			{1, 0, 0},{0, 1, 0},{-1, 0, 0},{0, -1, 0}, {0, 0, 1}, {0, 0, -1}
		};
		Triangulate(detailLevel, v[0], v[1], v[4], meshBuilder);
		Triangulate(detailLevel, v[1], v[2], v[4], meshBuilder);
		Triangulate(detailLevel, v[2], v[3], v[4], meshBuilder);
		Triangulate(detailLevel, v[3], v[0], v[4], meshBuilder);
		Triangulate(detailLevel, v[1], v[0], v[5], meshBuilder);
		Triangulate(detailLevel, v[2], v[1], v[5], meshBuilder);
		Triangulate(detailLevel, v[3], v[2], v[5], meshBuilder);
		Triangulate(detailLevel, v[0], v[3], v[5], meshBuilder);

		m_Meshes[PrimitiveMeshType::Sphere] = meshBuilder.Build();
	}
	static void Triangulate(uint32_t detailLevel, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, MeshBuilder& meshBuilder)
	{
		if (detailLevel <= 0)
		{
			uint32_t indexA = meshBuilder.AddVertex(a, a, { 0,0 });
			uint32_t indexB = meshBuilder.AddVertex(b, b, { 0,0 });
			uint32_t indexC = meshBuilder.AddVertex(c, c, { 0,0 });
			meshBuilder.AddTriangle(indexA, indexB, indexC);
		}
		else
		{
			glm::vec3 ab = glm::normalize((a + b) / 2.0f);
			glm::vec3 bc = glm::normalize((b + c) / 2.0f);
			glm::vec3 ca = glm::normalize((c + a) / 2.0f);
			Triangulate(detailLevel - 1, a, ab, ca, meshBuilder);
			Triangulate(detailLevel - 1, b, bc, ab, meshBuilder);
			Triangulate(detailLevel - 1, c, ca, bc, meshBuilder);
			Triangulate(detailLevel - 1, ab, bc, ca, meshBuilder);
		}
	}
}
