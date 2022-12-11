#pragma once

#include <chrono>

#include "export.h"

class DLLEXPORT Timer
{
public:
	Timer();
	~Timer();

private:
	std::chrono::time_point<std::chrono::system_clock> start;
};