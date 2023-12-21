#pragma once

#include "Ramensoup/Scene/Entity.h"

namespace Ramensoup
{
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
}