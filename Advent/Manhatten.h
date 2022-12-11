#pragma once

#include <string>
#include <vector>

namespace Day12
{
	struct Instruction
	{
		char type;
		int value;
	};

	enum class Direction
	{
		North,
		East,
		South,
		West
	};

	struct Point
	{
		int x;
		int y;
	};

	std::vector<Instruction> ParseFile(const std::string& file);
	void Part1(const std::vector<Instruction>& inputs);
	void Part2(const std::vector<Instruction>& inputs);

	Direction TurnAntiClockwise(Direction d, int times);
	Direction TurnClockwise(Direction d, int times);

	Point RotateAntiClockwise(Point p, int angle);
}