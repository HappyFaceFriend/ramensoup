#pragma once

#include "Ramensoup/Renderer/Mesh.h"
#include "Ramensoup/Renderer/Material.h"

#include <memory>

namespace Ramensoup
{
	struct MeshRendererComponent
	{
		std::shared_ptr<Mesh> Mesh;
		std::shared_ptr<Material> Material;

		MeshRendererComponent() = default;
	};
}