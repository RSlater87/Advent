#pragma once

#include <vector>
#include <string>

namespace CalorieCounter
{
	std::vector<std::vector<int>> ParseInput(const std::string& filename);

	void Part1_FindMaxCalories(const std::vector<std::vector<int>> caloriesPerElf);
	void Part2_FindTopThreeCalories(const std::vector<std::vector<int>> caloriesPerElf);
}
