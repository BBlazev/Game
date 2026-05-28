#include "include/scoped_timer.hpp"

ScopedTimer::ScopedTimer(float& variable) : var(variable)
{
	t0 = std::chrono::steady_clock::now();
}

ScopedTimer::~ScopedTimer()
{
	t1 = std::chrono::steady_clock::now();
	var = std::chrono::duration<float, std::milli>(t1 - t0).count();
}
