#pragma once
#include <chrono>


class ScopedTimer
{
public:

	ScopedTimer(float& variable);
	~ScopedTimer();
private:

	auto starting_point;
	auto ending_point;

};