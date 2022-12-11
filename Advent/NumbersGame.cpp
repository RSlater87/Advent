#include "NumbersGame.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <numeric>
#include <deque>
#include <unordered_map>

void Day15::NumbersGame_Map(const std::vector<int>& start, int target)
{
	Timer t;
	std::unordered_map<int, std::deque<int>> mapOfIndexes;

	int i = 1;
	int previousNumber = start.front();
	for (auto& seed : start)
	{
		mapOfIndexes[seed].push_back(i);
		previousNumber = seed;
		++i;
	}

	int percentageStep = target / 10;

	for (; i < target + 1; ++i)
	{
		if (i % percentageStep == 0)
		{
			std::cout << i / percentageStep << std::endl;
		}

		if (mapOfIndexes[previousNumber].size() == 1)
		{
			mapOfIndexes[0].push_back(i);
			previousNumber = 0;
		}
		else
		{
			auto lastIndex = mapOfIndexes[previousNumber].end() - 1;
			auto nextNumber = *(lastIndex) - *(lastIndex - 1);
			mapOfIndexes[nextNumber].push_back(i);
			if (mapOfIndexes[nextNumber].size() > 2)
			{
				mapOfIndexes[nextNumber].pop_front();
			}
			previousNumber = nextNumber;
		}
	}

	std::cout << previousNumber << std::endl;
}

void Day15::NumbersGame_Vector(const std::vector<int>& start, int target)
{
	//First tried this with unordered_map, it takes like 5mins to finish with Part 2
	//Vector just takes 7s :U
	Timer t;
	std::vector<std::pair<int, int>> turns(target);
	std::vector<int> spoken(target);

	int i = 0;
	int previous = start.front();
	for (auto& num : start)
	{
		auto& p = turns[num];
		p.second = std::exchange(p.first, ++i);
		++spoken[num];
		previous = num;
	}

	for (; i < target;)
	{
		int current = spoken[previous] == 1
			? 0
			: i - turns[previous].second;

		auto& p = turns[current];
		p.second = std::exchange(p.first, ++i);
		++spoken[current];
		previous = current;
	}

	std::cout << previous << std::endl;
}