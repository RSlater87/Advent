#pragma once
#include <string>
#include <set>
#include <vector>

#include "../AdventUtility/Point.h"

namespace RopeTracking
{
	void Part1(const std::string& filename);

	void Part2(const std::string& filename);

	void MoveRopeChain(std::vector<std::string>& allLines, std::vector<Point>& points, std::set<Point>& tailPositions);

	void MoveX(std::vector<Point>& p, int size, int step, std::set<Point>& tailPositions);
	void MoveY(std::vector<Point>& p, int size, int step, std::set<Point>& tailPositions);
	bool IsAdjacent(Point& head, Point& tail);
}
