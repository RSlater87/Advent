#include "Manhatten.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>

namespace
{
	const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923;
	const double DEG_TO_RAD = PI / 180.0;
}

std::vector<Day12::Instruction> Day12::ParseFile(const std::string& file)
{
	std::vector<std::string> lines = SplitString(ReadAllText(file), "\n");

	std::vector<Instruction> inputs;
	std::transform(lines.cbegin(), lines.cend(), std::back_inserter(inputs), [&](const std::string& line)
		{
			return Instruction{ line[0], std::stoi(line.substr(1)) };
		});

	return inputs;
}

void Day12::Part1(const std::vector<Instruction>& inputs)
{
	Timer t;

	Direction d = Direction::East;
	int ew_units = 0;
	int ns_units = 0;

	for (auto& instruction : inputs)
	{
		switch (instruction.type)
		{
		case 'N':
			ns_units += instruction.value;
			break;
		case 'E':
			ew_units += instruction.value;
			break;
		case 'S':
			ns_units -= instruction.value;
			break;
		case 'W':
			ew_units -= instruction.value;
			break;
		case 'L':
			d = TurnAntiClockwise(d, instruction.value / 90);
			break;
		case 'R':
			d = TurnClockwise(d, instruction.value / 90);
			break;
		case 'F':
		{
			switch (d)
			{
			case Day12::Direction::North:
				ns_units += instruction.value;
				break;
			case Day12::Direction::East:
				ew_units += instruction.value;
				break;
			case Day12::Direction::South:
				ns_units -= instruction.value;
				break;
			case Day12::Direction::West:
				ew_units -= instruction.value;
				break;
			default:
				break;
			}
		}
		break;
		}
	}

	std::cout << "Manhattan Distance: " << std::abs(ns_units) + std::abs(ew_units) << std::endl;
}

void Day12::Part2(const std::vector<Instruction>& inputs)
{
	auto start = std::chrono::system_clock::now();

	Direction d = Direction::East;
	Point ship{ 0, 0 };
	Point waypoint{ 10, 1 };
	int waypoint_ns = 1;
	int waypoint_ew = 10;

	for (auto& instruction : inputs)
	{
		switch (instruction.type)
		{
		case 'N':
			waypoint.y += instruction.value;
			break;
		case 'E':
			waypoint.x += instruction.value;
			break;
		case 'S':
			waypoint.y -= instruction.value;
			break;
		case 'W':
			waypoint.x -= instruction.value;
			break;
		case 'L':
			waypoint = RotateAntiClockwise(waypoint, instruction.value);
			break;
		case 'R':
			waypoint = RotateAntiClockwise(waypoint, 360 - instruction.value);
			break;
		case 'F':
			ship.y += (instruction.value * waypoint.y);
			ship.x += (instruction.value * waypoint.x);
			break;
		}
	}

	std::cout << "Manhattan Distance: " << std::abs(ship.y) + std::abs(ship.x) << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

Day12::Direction Day12::TurnAntiClockwise(Direction d, int times)
{
	for (int rotation = 0; rotation < times; ++rotation)
	{
		switch (d)
		{
		case Day12::Direction::North:
			d =  Direction::West;
			break;
		case Day12::Direction::East:
			d =  Direction::North;
			break;
		case Day12::Direction::South:
			d =  Direction::East;
			break;
		case Day12::Direction::West:
			d =  Direction::South;
			break;
		}
	}

	return d;
}

Day12::Direction Day12::TurnClockwise(Direction d, int times)
{
	for (int rotation = 0; rotation < times; ++rotation)
	{
		switch (d)
		{
		case Day12::Direction::North:
			d =  Direction::East;
			break;
		case Day12::Direction::East:
			d =  Direction::South;
			break;
		case Day12::Direction::South:
			d =  Direction::West;
			break;
		case Day12::Direction::West:
			d =  Direction::North;
			break;
		}
	}

	return d;
}

Point Day12::RotateAntiClockwise(Point p, int angle)
{
	return Point{
		(int)std::round(p.x * std::cos(angle * DEG_TO_RAD) - p.y * sin(angle * DEG_TO_RAD)),
		(int)std::round(p.x * std::sin(angle * DEG_TO_RAD) + p.y * cos(angle * DEG_TO_RAD))
	};
}