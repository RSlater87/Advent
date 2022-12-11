#pragma once
#include <map>
#include <string>

#include "../AdventUtility/Point.h"

namespace TreeMap
{
	//Parse input file into a simple map of trees
	std::map<Point, char> ParseInputs(const std::string& filename);

	void Part1(const std::map<Point, char>& treeMap);

	void Part2(const std::map<Point, char>& treeMap);
	int CalculateScenicScore(const int& x, const int& y, const std::map<Point, char>& treeMap);
}