#pragma once

#include <Ramensoup.h>

namespace Ramensoup
{
	class EditorGUI
	{
	public:
		EditorGUI() = delete;

		static bool InputText(const zstring_view& label, char* buffer, size_t size);
		static bool Vector3Field(const zstring_view& label, glm::vec3& vector);
		static bool ColorField(const zstring_view& label, glm::vec3& color);
		static bool ColorField(const zstring_view& label, glm::vec4& color);
		static bool DraggableFloatField(const zstring_view& label, float* value);
		static bool SelectableField(const zstring_view& label, const char* options[], uint32_t optionCount, uint32_t& selectedIndex);

		static void SetLabelWidth(uint32_t width) { s_LabelWidth = width; }
		static uint32_t GetDefaultLabelWidth() { return s_LabelWidth; }
	private:
		static uint32_t s_LabelWidth;
	};
}