#pragma once

#ifdef RS_DEBUG
	#define RS_ENABLE_ASSERTS
	#define RS_ENABLE_LOGS
	#define RS_ENABLE_PROFILING
#endif //ifdef RS_DEBUG

#ifdef RS_ENABLE_ASSERTS
	#define RS_CORE_ASSERT(x) if(!(x)) __debugbreak();
	#define RS_CORE_ASSERT(x, ...) if(!(x)) {RS_CORE_LOG_ERROR(__VA_ARGS__);__debugbreak();}
#else //ifdef RS_ENABLE_ASSERTS
	#define RS_CORE_ASSERT(x)
	#define RS_CORE_ASSERT(x, ...)
#endif //ifdef RS_ENABLE_ASSERTS else

#ifdef RS_ENABLE_LOGS
#include "Ramensoup/Debug/Logger.h"
#endif //ifdef RS_ENABLE_LOGS

#ifdef RS_ENABLE_PROFILING
#include "Ramensoup/Debug/ProfileLayer.h"
#endif
