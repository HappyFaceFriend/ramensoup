#pragma once

#include "Logger.h"

#ifdef RS_DEBUG
	#define RS_ENABLE_ASSERTS
#endif

#ifdef RS_ENABLE_ASSERTS
	#define RS_CORE_ASSERT(x) if(!(x)) __debugbreak();
	#define RS_CORE_ASSERT(x, ...) if(!(x)) Ramensoup::CoreLogger::Error(__VA_ARGS__);__debugbreak();
#endif