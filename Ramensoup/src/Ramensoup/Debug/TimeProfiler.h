#pragma once

#include <chrono>
#include <unordered_map>
#include <unordered_set>

namespace Ramensoup
{
	class TimeProfiler
	{
	public:
		struct Item
		{
			using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
			TimePoint Start;
			TimePoint End;
			double Miliseconds= 0;
		};

	private:
		TimeProfiler() = default;
	public:
		~TimeProfiler() = default;
		TimeProfiler(const TimeProfiler&) = delete;
		TimeProfiler(TimeProfiler&&) = delete;
		TimeProfiler& operator=(const TimeProfiler&) = delete;
		TimeProfiler& operator=(TimeProfiler&&) = delete;

	public:
		static void Begin(const std::string& key);
		static void End(const std::string& key);

		[[nodiscard]] inline static TimeProfiler& Get() { return *s_Instance; }

		inline const Item& GetProfileItem(const std::string& key) const { return m_ProfileItems.at(key); }
		inline const std::unordered_set<std::string>& GetProfileKeys() const { return m_Keys;  }

	private:
		static TimeProfiler *s_Instance;

	private:
		std::unordered_map<std::string, Item> m_ProfileItems;
		std::unordered_set<std::string> m_Keys;
	};
}