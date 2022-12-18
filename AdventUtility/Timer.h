#pragma once

#include <chrono>

#include "export.h"

//Just ignore C4251 here
#pragma warning( push )
#pragma warning( disable: 4251 )

class DLLEXPORT Timer
{
public:
	Timer();
	~Timer();

	double SoFar();

private:
	std::chrono::time_point<std::chrono::system_clock> start;
};

#pragma warning( pop )