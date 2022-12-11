#include "RopeTracking.h"
#include "RopeTracking.h"
#include "../AdventUtility/Utilities.h"
#include <set>
#include <iostream>

void RopeTracking::Part1(const std::string& filename)
{
	auto allLines = SplitString(ReadAllText(filename), "\n");

	std::vector<Point> points = { 2, Point{ 0, 0 } };
	std::set<Point> tailPositions = { Point{ 0, 0 } };

	MoveRopeChain(allLines, points, tailPositions);

	std::cout << tailPositions.size() << std::endl;
}

void RopeTracking::Part2(const std::string& filename)
{
	auto allLines = SplitString(ReadAllText(filename), "\n");
	std::vector<Point> points = { 10, Point{ 0, 0 } };
	std::set<Point> tailPositions = { Point{ 0, 0 } };

	MoveRopeChain(allLines, points, tailPositions);

	std::cout << tailPositions.size() << std::endl;
}

void RopeTracking::MoveRopeChain(std::vector<std::string>& allLines, std::vector<Point>& points, std::set<Point>& tailPositions)
{
	for (auto line : allLines)
	{
		auto parts = SplitString(line, " ");

		std::string direction = parts[0];
		int space = std::stoi(parts[1]);

		if (direction == "L")
		{
			MoveX(points, space, -1, tailPositions);
		}
		else if (direction == "R")
		{
			MoveX(points, space, 1, tailPositions);
		}
		else if (direction == "U")
		{
			MoveY(points, space, +1, tailPositions);
		}
		else if (direction == "D")
		{
			MoveY(points, space, -1, tailPositions);
		}
	}
}

void RopeTracking::MoveX(std::vector<Point>& p, int size, int step, std::set<Point>& tailPositions)
{
	for (int i = 0; i < size; i += 1)
	{
		for (size_t pi = 0; pi < p.size(); ++pi)
		{
			if (pi == 0)
			{
				p[pi].x += step;
			}
			else
			{
				//T is not adjacent
				auto& head = p[pi - 1];
				auto& tail = p[pi];
				if (!IsAdjacent(head, tail))
				{
					if (tail.y == head.y)
					{
						tail.x += step;
					}
					else
					{
						tail.y += sgn(head.y - tail.y);
						tail.x += sgn(head.x - tail.x);
					}

					if (pi == p.size() - 1)
					{
						tailPositions.insert(tail);
					}
				}
			}
		}
	}
}

void RopeTracking::MoveY(std::vector<Point>& p, int size, int step, std::set<Point>& tailPositions)
{
	for (int i = 0; i < size; i += 1)
	{
		for (size_t pi = 0; pi < p.size(); ++pi)
		{
			if (pi == 0)
			{
				p[pi].y += step;
			}
			else
			{
				//T is not adjacent
				auto& head = p[pi - 1];
				auto& tail = p[pi];
				if (!IsAdjacent(head, tail))
				{
					if (tail.x == head.x)
					{
						tail.y += step;
					}
					else
					{
						tail.y += sgn(head.y - tail.y);
						tail.x += sgn(head.x - tail.x);
					}

					if (pi == p.size() - 1)
					{
						tailPositions.insert(tail);
					}
				}
			}
		}
	}
}

bool RopeTracking::IsAdjacent(Point& head, Point& tail)
{
	return std::abs(head.x - tail.x) < 2
		&& std::abs(head.y - tail.y) < 2;
}
