#include "CalorieCounter.h"
#include <numeric>
#include <algorithm>

#include "../AdventUtility/Utilities.h"
#include <iterator>
#include <iostream>

std::vector<std::vector<int>> CalorieCounter::ParseInput(const std::string& filename)
{
	std::string allLines = ReadAllText(filename);
	std::vector<std::string> splitLines = SplitString(allLines, "\n");

	std::vector<std::vector<int>> caloriesPerElf;
	std::vector<int> calories;
	for (auto& line : splitLines)
	{
		if (line.empty())
		{
			caloriesPerElf.push_back(calories);
			calories.clear();
		}
		else
		{
			calories.push_back(std::stoi(line));
		}
	}

	return caloriesPerElf;
}

void CalorieCounter::Part1_FindMaxCalories(const std::vector<std::vector<int>> caloriesPerElf)
{
	std::vector<int> totalCalories;
	std::transform(caloriesPerElf.cbegin(), caloriesPerElf.cend(), std::back_inserter(totalCalories),
		[&](const std::vector<int>& calories)
		{
			return std::accumulate(calories.cbegin(), calories.cend(), 0);
		});

	int maxCalories = (*std::max_element(totalCalories.cbegin(), totalCalories.cend()));

	std::cout << maxCalories << std::endl;
}

void CalorieCounter::Part2_FindTopThreeCalories(const std::vector<std::vector<int>> caloriesPerElf)
{
	std::vector<int> totalCalories;
	std::transform(caloriesPerElf.cbegin(), caloriesPerElf.cend(), std::back_inserter(totalCalories),
		[&](const std::vector<int>& calories)
		{
			return std::accumulate(calories.cbegin(), calories.cend(), 0);
		});

	std::sort(totalCalories.begin(), totalCalories.end(), std::greater<int>());

	int maxTopThree = std::accumulate(totalCalories.cbegin(), totalCalories.cbegin() + 3, 0);

	std::cout << maxTopThree << std::endl;
}
