#include "pch.h"
#include "TimeProfiler.h"

namespace Ramensoup
{
	TimeProfiler* TimeProfiler::s_Instance = new TimeProfiler();

	void TimeProfiler::Begin(const std::string& key)
	{
		s_Instance->m_Keys.insert(key);
		s_Instance->m_ProfileItems[key].Start = std::chrono::high_resolution_clock::now();
	}
	void TimeProfiler::End(const std::string& key)
	{
		auto& item = s_Instance->m_ProfileItems[key];
		item.End = std::chrono::high_resolution_clock::now();
		item.Miliseconds = (std::chrono::time_point_cast<std::chrono::microseconds>(item.End).time_since_epoch().count()
						- std::chrono::time_point_cast<std::chrono::microseconds>(item.Start).time_since_epoch().count()) / 1000.0;
	}
}