#include "pch.h"

#include "Logger.h"


namespace Ramensoup
{
	std::shared_ptr<spdlog::logger> Logger::s_Logger;
	std::shared_ptr<spdlog::logger> CoreLogger::s_Logger;


	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stdout_color_mt("APP");
		s_Logger->set_level(spdlog::level::trace);
	}
	void CoreLogger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stdout_color_mt("CORE");
		s_Logger->set_level(spdlog::level::trace);
	}
}