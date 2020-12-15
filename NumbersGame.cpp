#include "NumbersGame.h"
#include "Utilities.h"
#include "Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>

void Day15::NumbersGame(const std::vector<int>& start, int target)
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