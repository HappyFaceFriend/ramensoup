#pragma once

#include "Ramensoup/Utils/zstring_view.h"

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
}