#pragma once
#include <chrono>


class ScopedTimer
{
public:

	explicit ScopedTimer(float& variable);
	~ScopedTimer();

	ScopedTimer(const ScopedTimer& other)				= delete;
	ScopedTimer& operator=(const ScopedTimer& other)	= delete;
	ScopedTimer(ScopedTimer&& other)					= delete;
	ScopedTimer& operator=(ScopedTimer&& other)			= delete;

private:

	std::chrono::time_point<std::chrono::steady_clock> t0;
	std::chrono::time_point<std::chrono::steady_clock> t1;

	float& var;
	float start_time;
};