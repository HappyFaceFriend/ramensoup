#pragma once

#pragma warning(push)
#pragma warning(disable:4819)

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#pragma warning(pop)

namespace Ramensoup
{
	class Logger
	{
	public:
		static void Init();

		constexpr static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		constexpr static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		Logger() = delete;

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
#ifdef RS_ENABLE_LOGS
	#define RS_CORE_LOG(...)		::Ramensoup::Logger::GetCoreLogger()->trace(__VA_ARGS__)
	#define RS_CORE_LOG_INFO(...)	::Ramensoup::Logger::GetCoreLogger()->info(__VA_ARGS__)
	#define RS_CORE_LOG_WARN(...)	::Ramensoup::Logger::GetCoreLogger()->warn(__VA_ARGS__)
	#define RS_CORE_LOG_ERROR(...)	::Ramensoup::Logger::GetCoreLogger()->error(__VA_ARGS__)

	#define RS_LOG(...)			::Ramensoup::Logger::GetClientLogger()->trace(__VA_ARGS__)
	#define RS_LOG_INFO(...)	::Ramensoup::Logger::GetClientLogger()->info(__VA_ARGS__)
	#define RS_LOG_WARN(...)	::Ramensoup::Logger::GetClientLogger()->warn(__VA_ARGS__)
	#define RS_LOG_ERROR(...)	::Ramensoup::Logger::GetClientLogger()->error(__VA_ARGS__)

#else //ifdef RS_ENABLE_LOGS
	#define RS_CORE_LOG(...)		
	#define RS_CORE_LOG_INFO(...)	
	#define RS_CORE_LOG_WARN(...)	
	#define RS_CORE_LOG_ERROR(...)	

	#define RS_LOG(...)		
	#define RS_LOG_INFO(...)
	#define RS_LOG_WARN(...)
	#define RS_LOG_ERROR(...)

#endif //ifdef RS_ENABLE_LOGS else
