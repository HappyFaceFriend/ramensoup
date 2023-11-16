#include "pch.h"
#include "Time.h"


namespace Ramensoup
{
	std::chrono::time_point<std::chrono::high_resolution_clock> Time::s_LastTime = std::chrono::high_resolution_clock::now();
	float Time::s_DeltaTime;

	void Time::Tick()
	{
		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> diff = now - s_LastTime;

		s_DeltaTime = diff.count();

		s_LastTime = now;
	}

	float Time::GetDeltaTime()
	{
		return s_DeltaTime;
	}

}