#pragma once

#include <string>
#include <vector>
#include <map>

namespace Day10
{
	/// <summary>
	/// Lists cable value and the neigbouring cables that have a 1, 2, or 3 difference (in an increasing direction) 
	/// </summary>
	struct Cable
	{
		int value;
		std::map<int, int> Differences;
	};

	std::vector<Cable> ParseFile(const std::string& file);

	void Part1(const std::vector<Cable>& inputs);
	void Part2(const std::vector<Cable>& inputs);

	void TraverseByLongestRouteAndCountDifferences(const std::map<int, Cable>& adjacencyList, int index, int& one, int& three);
	void TraverseAndCountRoutesToEnd(const std::map<int, Cable>& adjacencyList, int index, std::map<int, size_t>& routes);

}