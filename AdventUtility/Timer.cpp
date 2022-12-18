#include "pch.h"

#include "Timer.h"
#include <iostream>


Timer::Timer()
{
	start = std::chrono::system_clock::now();
}

Timer::~Timer()
{
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

double Timer::SoFar()
{
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	return diff.count();
}
