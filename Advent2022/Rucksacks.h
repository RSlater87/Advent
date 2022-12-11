#pragma once
#include <string>
#include <vector>

namespace Rucksacks
{
	struct Rucksack
	{
		std::string left;
		std::string right;
	};

	struct Group
	{
		std::string a;
		std::string b;
		std::string c;
	};

	std::vector<Rucksack> ParseInputs(const std::string& filename);

	std::vector<Group> ParseGroups(const std::vector<Rucksack>& rucksacks);

	std::string FindOverlaps(const std::vector<Rucksack>& rucksacks);

	std::string FindOverlaps(const std::vector<Group>& groups);
	std::string FindOverlap(std::string a, std::string b);

	int FindTotalPriority(const std::string& priorities);

	void Part1(const std::vector<Rucksack>& rucksacks);
	void Part2(const std::vector<Rucksack>& rucksacks);
}