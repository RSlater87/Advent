#pragma once

#include <string>
#include <vector>

namespace Day9
{
	std::vector<int> ParseFile(const std::string& file);
	int Part1(const std::vector<int>& numbers);
	void Part2(const std::vector<int>& numbers, int invalidNumber);
}
