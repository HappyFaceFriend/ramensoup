#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class EditorGUI
	{
	public:
		EditorGUI() = delete;

		static bool InputText(const zstring_view& label, char* buffer, size_t size);
		static bool EditorGUI::Vector3Field(const zstring_view& label, glm::vec3& vector);

	};
}