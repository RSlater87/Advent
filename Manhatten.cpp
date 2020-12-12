#include "Manhatten.h"
#include "Utilities.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <chrono>
#include <numeric>

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
	auto start = std::chrono::system_clock::now();

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

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

void Day12::Part2(const std::vector<Instruction>& inputs)
{
	auto start = std::chrono::system_clock::now();

	Direction d = Direction::East;
	int ship_ns = 0;
	int ship_ew = 0;
	int waypoint_ns = 1;
	int waypoint_ew = 10;

	for (auto& instruction : inputs)
	{
		switch (instruction.type)
		{
		case 'N':
			waypoint_ns += instruction.value;
			break;
		case 'E':
			waypoint_ew += instruction.value;
			break;
		case 'S':
			waypoint_ns -= instruction.value;
			break;
		case 'W':
			waypoint_ew -= instruction.value;
			break;
		case 'L':
			RotateAntiClockwise(waypoint_ew, waypoint_ns, instruction.value / 90);
			break;
		case 'R':
			RotateClockwise(waypoint_ew, waypoint_ns, instruction.value / 90);
			break;
		case 'F':
			ship_ns += (instruction.value * waypoint_ns);
			ship_ew += (instruction.value * waypoint_ew);
			break;
		}
	}

	std::cout << "Manhattan Distance: " << std::abs(ship_ns) + std::abs(ship_ew) << std::endl;

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

void Day12::RotateAntiClockwise(int& x, int& y, int times)
{
	for (int rotation = 0; rotation < times; ++rotation)
	{
		std::swap(x, y);
		x = -x;
	}
}

void Day12::RotateClockwise(int& x, int& y, int times)
{
	for (int rotation = 0; rotation < times; ++rotation)
	{
		std::swap(x, y);
		y = -y;
	}
}