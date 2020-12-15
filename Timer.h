#pragma once

#include <chrono>

class Timer
{
public:
	Timer();
	~Timer();

private:
	std::chrono::time_point<std::chrono::system_clock> start;
};