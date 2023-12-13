#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class EditorGUI
	{
	public:
		EditorGUI() = delete;

		static bool InputText(const zstring_view& label, char* buffer, size_t size);

	};
}