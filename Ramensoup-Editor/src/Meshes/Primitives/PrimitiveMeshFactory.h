#pragma once

#include "Ramensoup.h"

namespace Ramensoup
{
	enum class PrimitiveMeshType
	{
		Sphere
	};
	class PrimitiveMeshFactory
	{
	public:
		static std::shared_ptr<Mesh> Create(PrimitiveMeshType meshType);
		static std::shared_ptr<Mesh> CreateOrGet(PrimitiveMeshType meshType);

		static constexpr uint32_t DefaultSphereDetailLevel = 4;

	private:
		static void GenerateSphere(int detailLevel = DefaultSphereDetailLevel);

	private:
		static std::map<PrimitiveMeshType, std::shared_ptr<Mesh>> m_Meshes;

	};
}