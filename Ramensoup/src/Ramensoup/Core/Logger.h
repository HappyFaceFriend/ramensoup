#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ramensoup
{
	void InitLoggers();

	class Logger
	{
	public:
		template<typename... Args>
		using FormattedString = spdlog::format_string_t<Args...>;
	public:
		static void Init();

		template<typename... Args>
		inline static void Log(FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->trace(format, std::forward<Args>(args)...);
#else
#endif
		}

		template<typename... Args>
		inline static void Info(FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->info(format, std::forward<Args>(args)...);
#else
#endif
		}

		template<typename... Args>
		inline static void Warning(FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->warn(format, std::forward<Args>(args)...);
#else
#endif
		}

		template<typename... Args>
		inline static void Error(FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->error(format, std::forward<Args>(args)...);
#else
#endif
		}
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};


	class CoreLogger
	{
	public:
		static void Init();

		template<typename... Args>
		inline static void Log(Logger::FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->trace(format, std::forward<Args>(args)...);
#else
#endif
		}

		template<typename... Args>
		inline static void Info(Logger::FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->info(format, std::forward<Args>(args)...);
#else
#endif
		}

		template<typename... Args>
		inline static void Warning(Logger::FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->warn(format, std::forward<Args>(args)...);
#else
#endif
		}

		template<typename... Args>
		inline static void Error(Logger::FormattedString<Args...> format, Args &&... args)
		{
#ifdef RS_DEBUG
			s_Logger->error(format, std::forward<Args>(args)...);
#else
#endif
		}
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}