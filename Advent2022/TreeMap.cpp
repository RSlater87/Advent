#include "TreeMap.h"

#include "../AdventUtility/Utilities.h"
#include <iostream>

const int Size = 99;

std::map<Point, char> TreeMap::ParseInputs(const std::string & filename)
{
	auto allText = ReadAllText(filename);
	auto allLines = SplitString(allText, "\n");

	std::map<Point, char> points;
	for (int y = 0; y < Size; ++y)
	{
		for (int x = 0; x < Size; ++x)
		{
			points.insert(std::make_pair(Point{ x, y }, allLines[y][x]));
		}
	}

	return points;
}

void TreeMap::Part1(const std::map<Point, char>& treeMap)
{
	//This keeps track of what is the max value in a particular direction for each point
	std::map<Point, char> left, right, up, down;

	for (int y = 0; y < Size; ++y)
	{
		for (int x = 0; x < Size; ++x)
		{
			//Left -> 0 -> 99
			Point current{ x, y }, prev{x - 1, y};
			if (x == 0) //edge
			{
				left[current] = treeMap.at(current);
			}
			else
			{
				left[current] = std::max(treeMap.at(current), left.at(prev));
			}

			//Down -> 0 -> 99
			prev = Point{ x, y - 1 };
			if (y == 0)
			{
				down[current] = treeMap.at(current);
			}
			else
			{
				down[current] = std::max(treeMap.at(current), down.at(prev));
			}

			//Right -> 99 -> 0
			current = Point{ Size - x - 1, y };
			prev = Point{ Size - x, y };
			if (x == 0)
			{
				right[current] = treeMap.at(current);
			}
			else
			{
				right[current] = std::max(treeMap.at(current), right.at(prev));
			}

			//Up -> 99 -> 0
			current = Point{ x, Size - y - 1 };
			prev = Point{ x, Size - y };
			if (y == 0)
			{
				up[current] = treeMap.at(current);
			}
			else
			{
				up[current] = std::max(treeMap.at(current), up.at(prev));
			}
		}
	}

	//A point is *visible* if it is greater than *at-least* one of the max in the surrounding points
	size_t howManyAreVisible = 0;
	for (int y = 0; y < Size; ++y)
	{
		for (int x = 0; x < Size; ++x)
		{
			if (x == 0 || y == 0 || x == Size - 1 || y == Size - 1)
			{
				howManyAreVisible++;
				continue;
			}

			char tree = treeMap.at({ x, y });
			if (tree > left[{x - 1, y}] || tree > right[{x + 1, y}]
				|| tree > up[{x, y + 1}] || tree > down[{x, y - 1}])
			{
				howManyAreVisible++;
			}
		}
	}

	std::cout << howManyAreVisible << std::endl;
}

void TreeMap::Part2(const std::map<Point, char>& treeMap)
{
	//Naive implmentation - look-ahead until we hit something bigger to calculate the scenic score each time
	size_t maxScore = 0;

	for (int y = 0; y < Size; ++y)
	{
		for (int x = 0; x < Size; ++x)
		{
			size_t scenicScore = CalculateScenicScore(x, y, treeMap);
			maxScore = std::max(maxScore, scenicScore);
		}
	}

	std::cout << maxScore << std::endl;
}

int TreeMap::CalculateScenicScore(const int& x, const int& y, const std::map<Point, char>& treeMap)
{
	if (x == 0 || y == 0 || x == Size - 1 || y == Size - 1)
	{
		return 0;
	}

	char tree = treeMap.at({ x, y });

	int x0;
	for (x0 = x - 1; x0 > 0; x0--)
	{
		if (treeMap.at({ x0, y }) >= tree)
		{
			break;
		}
	}
	int lookLeft = x - x0;

	for (x0 = x + 1; x0 < Size - 1; x0++)
	{
		if (treeMap.at({ x0, y }) >= tree)
		{
			break;
		}
	}
	int lookRight = x0 - x;

	int y0;
	for (y0 = y - 1; y0 > 0; y0--)
	{
		if (treeMap.at({ x, y0 }) >= tree)
		{
			break;
		}
	}
	int lookUp = y - y0;

	for (y0 = y + 1; y0 < Size - 1; y0++)
	{
		if (treeMap.at({ x, y0 }) >= tree)
		{
			break;
		}
	}
	int lookDown = y0 - y;

	int scenicScore = lookLeft * lookRight * lookUp * lookDown;
	return scenicScore;
}
