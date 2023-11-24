#pragma once

#ifndef __RS_MACRO_SET__ //GUARD
#define __RS_MACRO_SET__

#ifdef RS_DEBUG
	#define RS_ENABLE_ASSERTS
	#define RS_ENABLE_LOGS
	#define RS_ENABLE_PROFILING
#endif //ifdef RS_DEBUG

#ifdef RS_ENABLE_ASSERTS
	#define RS_CORE_ASSERT(x, ...) if(!(x)) {RS_CORE_LOG_ERROR(__VA_ARGS__);__debugbreak();}
#else //ifdef RS_ENABLE_ASSERTS
	#define RS_CORE_ASSERT(x, ...)
#endif //ifdef RS_ENABLE_ASSERTS else

#ifdef RS_ENABLE_LOGS
#include "Ramensoup/Debug/Logger.h"
#endif //ifdef RS_ENABLE_LOGS

#endif //__RS_MACRO_SET__