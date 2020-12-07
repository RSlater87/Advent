#pragma once

#include <string>
#include <vector>
#include <map>

namespace Day7
{
	struct Child
	{
		int quantity;
		std::string innerBag;
	};

	struct Vertex
	{
		std::vector<std::string> parents;
		std::vector<Child> children;
	};

	/// <summary>
	/// Create a Adjacency List representing the graph of the luggage in the referenced file
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	std::map<std::string, Vertex> ParseFile(const std::string& filename);

	/// <summary>
	/// Recursively finds the total parent keys for the supplied key
	/// </summary>
	/// <param name="luggageGraph"></param>
	/// <returns></returns>
	std::vector<std::string> FindTotalParentsKeys(const std::map<std::string, Vertex>& luggageGraph, const std::string& key);

	/// <summary>
	/// Recursively find the total number of children for the supplied key
	/// </summary>
	/// <param name="luggageGraph"></param>
	/// <param name="key"></param>
	/// <returns></returns>
	size_t FindTotalChildrenCount(const std::map <std::string, Vertex>& luggageGraph, const std::string& key);

	/// <summary>
	/// Works out the answer for Part 1
	/// </summary>
	/// <param name="luggageGraph"></param>
	void Part1(const std::map<std::string, Vertex>& luggageGraph);

	/// <summary>
	/// Works out the answer for Part 2
	/// </summary>
	/// <param name="luggageGraph"></param>
	void Part2(const std::map<std::string, Vertex>& luggageGraph);
}