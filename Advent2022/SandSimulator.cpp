#include "SandSimulator.h"
#include "../AdventUtility/Utilities.h"
#include <regex>
#include <fstream>
#include <iostream>
#include "../AdventUtility/Timer.h"

/// <summary>
/// Produce a Cave map with the rock barriers filled in, from the file of paths.
/// </summary>
/// <param name="filename"></param>
/// <returns></returns>
SandSimulator::CaveMap SandSimulator::ParseFile(const std::string& filename)
{
	auto allLines = SplitString(ReadAllText(filename), "\n");

	std::vector<std::vector<Point>> paths;

	//height and width of the map is the deepest rock barrier 
	size_t height = std::numeric_limits<size_t>().min(), width = std::numeric_limits<size_t>().min();

	//Each line in the input file should contain a list of numbers, iterate over it in pair of X, then Y using regex
	for (auto& line : allLines)
	{
		std::regex numMatch(R"(\d+)");
		std::sregex_iterator iter(line.begin(), line.end(), numMatch);
		std::sregex_iterator end;

		std::vector<Point> path;
		while (iter != end)
		{
			Point p;
			p.x = std::stoi(iter++->str());
			p.y = std::stoi(iter++->str());
			width = std::max(width, static_cast<size_t>(p.x));
			height = std::max(height, static_cast<size_t>(p.y));
			path.push_back(p);
		}
		paths.push_back(path);
	}

	//Map fiddles - add a gap at the end for sand to look into
	height += 2;
	width += height; //so sand can go triangular

	//Start my map as filled with air
	CaveMap caveMap = { Point{500, 0}, height, width, {width, { height, State::Air} } };

	//Draw rock paths onto map
	for (auto path : paths)
	{
		for (auto left = path.begin(), right = path.begin() + 1;
			right != path.end();
			left++, right++)
		{
			if (left->x == right->x) //Draw along Y-axis
			{
				__int64 start = std::min(left->y, right->y), end = std::max(left->y, right->y);
				for (__int64 py = start; py <= end; ++py)
				{
					caveMap.caveMap[left->x][py] = State::Rock;
				}
			}
			else					//Draw along X-axis
			{
				__int64 start = std::min(left->x, right->x), end = std::max(left->x, right->x);
				for (__int64 px = start; px <= end; ++px)
				{
					caveMap.caveMap[px][left->y] = State::Rock;
				}
			}
		}
	}

	//Dump to output file the current state
	ExportCaveMap(caveMap, "export.txt");

	return caveMap;
}

/// <summary>
/// Starting at sand source, look downwards until you hit a rock barrier,
/// Then test if there's free space left or right
/// If neither, come to 'rest', otherwise keep seeking, favour left path
/// If hit end of map before placing sand, return false.
/// if sand is already at source then source is blocked, so return false.
/// </summary>
/// <param name="cavemap">Cavemap to update</param>
/// <returns>True if sand was placed, otherwise false.</returns>
bool SandSimulator::SpawnSand(CaveMap& cavemap)
{
	//Starting at sand source, seek straight down until we can hit sand or rock
	static const std::vector<State> Barriers = { State::Rock, State::Sand };
	auto currentX = cavemap.caveMap.begin() + cavemap.sandSource.x;
	auto currentY = (*currentX).begin() + cavemap.sandSource.y;

	//If sand is at rest in source, break early
	if ((*currentY) == State::Sand)
	{
		return false;
	}
	
	while (currentY != (*currentX).end())
	{
		//advance to nearest barrier
		currentY = std::find_first_of(currentY, (*currentX).end(),
			Barriers.cbegin(), Barriers.cend());

		if (currentY == (*currentX).end())
		{
			//Hit end of image, break
			break;
		}

		//Look left and right
		size_t distance = std::distance((*currentX).begin(), currentY);
		auto left = (*(currentX - 1)).begin() + distance;
		auto right = (*(currentX + 1)).begin() + distance;

		bool leftIsBarrier = std::find(Barriers.cbegin(), Barriers.cend(), *left) != Barriers.cend();
		bool rightIsBarrier = std::find(Barriers.cbegin(), Barriers.cend(), *right) != Barriers.cend();

		if (leftIsBarrier && rightIsBarrier)
		{
			//Place sand just above here and exit
			currentY--;
			(*currentY) = State::Sand;
			return true;
		}
		else if(!leftIsBarrier)
		{
			//Favour going left over right
			currentX--;
			currentY = (*currentX).begin() + distance;
			continue; //continue search
		}
		else if (!rightIsBarrier)
		{
			currentX++;
			currentY = (*currentX).begin() + distance;
			continue; //continue search
		}
	}
	//Hit the bottom without finding a barrier to rest on - stop
	return false;
}

/// <summary>
/// Dump cave map out to a CSV file to examine
/// </summary>
/// <param name="map">map</param>
/// <param name="filename">path</param>
void SandSimulator::ExportCaveMap(CaveMap& map, const std::string& filename)
{
	std::ofstream ofs { filename };

	if (ofs.is_open())
	{
		for (size_t row = 0; row < map.height; ++row)
		{
			for (size_t col = 0; col < map.width; ++col)
			{
				ofs << (char) map.caveMap[col][row] << ',';
			}
			ofs << std::endl;
		}
	}

	ofs.close();
}

/// <summary>
/// Spawns sand until hit the end of the map, prints count.
/// </summary>
/// <param name="cavemap"></param>
void SandSimulator::Part1(CaveMap cavemap)
{
	Timer t;

	//Spawn sand until it starts hitting the bottom
	int count = 0;
	while (SpawnSand(cavemap))
	{
		count++;
	}

	//Dump to output file the current state
	ExportCaveMap(cavemap, "cave_part1.txt");

	std::cout << count << std::endl;
}

/// <summary>
/// Places a floor at the bottom of the cave, and then spawns sand until it can't.
/// Prints how much sand this takes.
/// </summary>
/// <param name="cavemap">Cavemap</param>
void SandSimulator::Part2(CaveMap cavemap)
{
	Timer t;

	//Place a floor at the bottom
	for (auto& column : cavemap.caveMap)
	{
		column.push_back(State::Rock);
	}
	cavemap.height++;

	//Spawn sand until it starts hitting the bottom
	int count = 0;
	while (SpawnSand(cavemap))
	{
		count++;
	}

	//Dump to output file the current state
	ExportCaveMap(cavemap, "cave_part2.txt");

	std::cout << count << std::endl;
}
