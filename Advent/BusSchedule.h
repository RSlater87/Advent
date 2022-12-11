#pragma once

#include <vector>
#include <string>
#include <map>

namespace Day13
{
	struct BusSchedule
	{
		int target;
		std::vector<int64_t> buses;
		std::vector<int64_t> remainders;
	};

	BusSchedule ParseFile(const std::string& file);
	void Part1(BusSchedule bs);
	void Part2(BusSchedule bs);
}