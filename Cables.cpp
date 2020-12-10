#include "Cables.h"
#include "Utilities.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <chrono>
#include <numeric>

std::vector<Day10::Cable> Day10::ParseFile(const std::string& file)
{
	std::ifstream fs{ file };
	std::vector<int> buffer = { 0 };
	while (fs.good())
	{
		int number;
		fs >> number;
		buffer.push_back(number);
	}

	//Sort to make it easier to find (since we'll look for differences ahead until diff is >3)
	std::sort(buffer.begin(), buffer.end());
	buffer.push_back(buffer.back() + 3);

	std::vector<Cable> inputs;
	for (auto outer = buffer.begin(); outer != buffer.end(); ++outer)
	{
		Cable node{ *outer };
		for (auto inner = outer + 1; inner != buffer.end(); ++inner)
		{
			int diff = *inner - *outer;
			if (InRange(diff, 1, 3))
			{
				node.Differences[diff] = (*inner);
			}
			else if(diff > 3)
			{
				break;
			}
		}

		inputs.push_back(node);
	}

	return inputs;
}

void Day10::Part1(const std::vector<Cable>& inputs)
{
	auto start = std::chrono::system_clock::now();

	auto one = std::count_if(inputs.cbegin(), inputs.cend(), [&](const Cable& c)
		{
			return c.Differences.find(1) != c.Differences.cend();
		});

	auto three = std::count_if(inputs.cbegin(), inputs.cend(), [&](const Cable& c)
		{
			return c.Differences.find(1) == c.Differences.cend()
				&& c.Differences.find(3) != c.Differences.cend();
		});

	std::cout << one * three << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

/// <summary>
/// Using the shortest-possible difference each time, traverse to the last node and get the jumps to get there each time
/// </summary>
void Day10::TraverseByLongestRouteAndCountDifferences(const std::map<int, Cable>& adjacencyList, int index, int& one, int& three)
{
	auto findKey = adjacencyList.at(index);

	//from the current index, look for the next index
	if (findKey.Differences.find(1) != findKey.Differences.cend())
	{
		TraverseByLongestRouteAndCountDifferences(adjacencyList, findKey.Differences[1], one, three);
		one++;
	}
	else if (findKey.Differences.find(3) != findKey.Differences.cend())
	{
		TraverseByLongestRouteAndCountDifferences(adjacencyList, findKey.Differences[3], one, three);
		three++;
	}
	else
	{
		//have hit end of graph, just exit
		return;
	}
}

void Day10::Part2(const std::vector<Cable>& inputs)
{
	auto start = std::chrono::system_clock::now();

	//Loop implementation - traverse backwards up the list and work out the possible routes
	std::map<int, size_t> routes;
	for (auto current = inputs.rbegin(); current != inputs.rend(); ++current)
	{
		auto node = *current;

		if (node.Differences.empty())
		{
			//hit end of graph, exit
			routes[node.value] = 1;
			continue;
		}

		size_t route = 0;
		for (auto& diff : node.Differences)
		{
			route += routes[diff.second];
		}

		routes[node.value] = route;
	}

	std::cout << routes[0] << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

void Day10::TraverseAndCountRoutesToEnd(const std::map<int, Cable>& adjacencyList, int index, std::map<int, size_t>& routes)
{
	auto findKey = adjacencyList.at(index);

	if (findKey.Differences.empty())
	{
		//hit end of graph, exit
		routes[index] = 1;
		return;
	}

	//fill the routes below this
	TraverseAndCountRoutesToEnd(adjacencyList, findKey.Differences.begin()->second, routes);

	size_t route = 0;
	for (auto& diff : findKey.Differences)
	{
		route += routes[diff.second];
	}
	
	//the number of routes for this is the sum of the route at each jump
	routes[index] = route;
}