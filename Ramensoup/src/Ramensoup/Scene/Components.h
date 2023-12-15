#pragma once

#include "Entity.h"

#include "Ramensoup/Renderer/Mesh.h"
#include "Ramensoup/Renderer/Material.h"
#include "Ramensoup/Utils/zstring_view.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <string>

namespace Ramensoup
{
	struct TagComponent
	{
		std::string Tag{""};

		TagComponent() = default;
		TagComponent(const zstring_view& tag)
			:Tag(tag) {}
	};

	//To change hierarchy, use Entity::SetParent()
	struct RelationshipComponent
	{
	public:
		[[nodiscard]] const Entity& GetParent() const noexcept { return m_Parent; }
		[[nodiscard]] const Entity& GetFirstChild() const noexcept { return m_FirstChild; }
		[[nodiscard]] const Entity& GetLastChild() const noexcept { return m_LastChild; }
		[[nodiscard]] const Entity& GetPrevSibling() const noexcept { return m_PrevSibling; }
		[[nodiscard]] const Entity& GetNextSibling() const noexcept { return m_NextSibling; }
	private:
		Entity m_Parent;
		Entity m_FirstChild;
		Entity m_LastChild;
		Entity m_PrevSibling;
		Entity m_NextSibling;

		friend Entity;
	};

	struct TransformComponent
	{
		glm::vec3 Position{0.0f, 0.0f, 0.0f};
		glm::vec3 Rotation{0.0f, 0.0f, 0.0f}; //In radians
		glm::vec3 Scale{1.0f, 1.0f, 1.0f};

		glm::mat4 ParentModelMatrix {1.0f};
		TransformComponent() = default;
		// TODO : Cache matrix and use isDirty to recalculate
		glm::mat4 GetMatrix() const
		{
			return ParentModelMatrix * glm::translate(glm::mat4(1.0f), Position) * glm::toMat4(glm::quat(Rotation)) * glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct MeshRendererComponent
	{
		std::shared_ptr<Mesh> Mesh;
		std::shared_ptr<Material> Material;

		MeshRendererComponent() = default;
	};
}