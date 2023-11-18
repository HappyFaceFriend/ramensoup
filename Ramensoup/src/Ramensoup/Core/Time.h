#pragma once

#include <chrono>

namespace Ramensoup
{
	class Time
	{
	public:
		static void Tick();

		static float GetDeltaTime();

		Time() = delete; 
	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> s_LastTime;
		static float s_DeltaTime;
	};
}