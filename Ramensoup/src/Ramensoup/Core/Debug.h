#pragma once

#include "Logger.h"

#ifdef RS_DEBUG
	#define RS_ENABLE_ASSERTS
#endif

#ifdef RS_ENABLE_ASSERTS
	#define RS_CORE_ASSERT(x) if(!(x)) __debugbreak();
	#define RS_CORE_ASSERT(x, ...) if(!(x)) {RS_CORE_LOG_ERROR(__VA_ARGS__);__debugbreak();}
#else
	#define RS_CORE_ASSERT(x)
	#define RS_CORE_ASSERT(x, ...)
#endif