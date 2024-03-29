#include "Luggage.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>

std::map<std::string, Day7::Vertex> Day7::ParseFile(const std::string& filename)
{
	Timer t;
	std::vector<std::string> inputs = SplitString(ReadAllText(filename), "\n");

	std::map<std::string, Vertex> adjacencyList;
	for (auto input : inputs)
	{
		if (input.empty())
		{
			continue;
		}

		//Break into parts so we can parse the list
		auto KeyAndChildren = SplitString(input, "contain");
		auto Key = Trim(RemoveFirst(KeyAndChildren[0], "bags"));
		auto Children = SplitString(KeyAndChildren[1], ",");

		//Create vector of children
		std::vector<Child> children;
		if (Children[0] != " no other bags.")
		{
			for (auto& child : Children)
			{
				auto parts = SplitString(Trim(child), ' ');

				Child c;
				c.quantity = std::stoi(parts[0]);		//Quantity
				c.innerBag = parts[1] + " " + parts[2];	//Colours are always two words long

				children.push_back(c);

				//update vertex list with parent
				adjacencyList[c.innerBag].parents.insert(Key);
			}
		}

		//Add to list
		adjacencyList[Key].children = children;
	}

	return adjacencyList;
}

std::set<std::string> Day7::FindTotalParentsKeys(const std::map<std::string, Vertex>& luggageGraph, const std::string& key)
{
	auto vertex = luggageGraph.at(key);

	if (vertex.parents.empty())
	{
		return {};
	}

	auto totalParents = vertex.parents;
	for (auto& parent : vertex.parents)
	{
		auto grandParents = FindTotalParentsKeys(luggageGraph, parent);
		totalParents.merge(grandParents);
	}

	return totalParents;
}

size_t Day7::FindTotalChildrenCount(const std::map <std::string, Vertex>& luggageGraph, const std::string& key)
{
	auto vertex = luggageGraph.at(key);

	if (vertex.children.empty())
	{
		return 0;
	}

	auto totalChildren = 0;
	for (auto& child : vertex.children)
	{
		auto grandChildren = FindTotalChildrenCount(luggageGraph, child.innerBag);
		totalChildren += (child.quantity + child.quantity * grandChildren);
	}

	return totalChildren;
}

void Day7::Part1(const std::map<std::string, Vertex>& luggageGraph)
{
	Timer t;

	auto totalParents = FindTotalParentsKeys(luggageGraph, "shiny gold");
	std::cout << totalParents.size() << std::endl;
}

void Day7::Part2(const std::map<std::string, Vertex>& luggageGraph)
{
	Timer t;

	auto totalParents = FindTotalChildrenCount(luggageGraph, "shiny gold");

	std::cout << totalParents << std::endl;
}