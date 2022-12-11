#include "Rucksacks.h"
#include <numeric>
#include <algorithm>

#include "../AdventUtility/Utilities.h"
#include <iterator>
#include <iostream>

std::vector<Rucksacks::Rucksack> Rucksacks::ParseInputs(const std::string& filename)
{
	auto allText = ReadAllText(filename);

	auto allLines = SplitString(allText, "\n");

	std::vector<Rucksack> rucksacks;
	for (auto& line : allLines)
	{
		if (line.empty())
			continue;

		size_t half = line.size() / 2;
		rucksacks.emplace_back(Rucksack{ line.substr(0, half), line.substr(half) });
	}

	return rucksacks;
}

std::vector<Rucksacks::Group> Rucksacks::ParseGroups(const std::vector<Rucksack>& rucksacks)
{
	std::vector<Rucksacks::Group> groups;
	for (size_t i = 0; i < rucksacks.size(); i += 3)
	{
		groups.emplace_back(Group{ rucksacks[i].left + rucksacks[i].right,
			rucksacks[i + 1].left + rucksacks[i + 1].right,
			rucksacks[i + 2].left + rucksacks[i + 2].right });
	}

	return groups;
}

std::string Rucksacks::FindOverlaps(const std::vector<Rucksack>& rucksacks)
{
	std::string overlaps;
	std::transform(rucksacks.cbegin(), rucksacks.cend(), std::back_inserter(overlaps), [&](Rucksack r)
		{
			return FindOverlap(r.left, r.right)[0];
		});

	return overlaps;
}

std::string Rucksacks::FindOverlaps(const std::vector<Group>& groups)
{
	std::string overlaps;
	std::transform(groups.cbegin(), groups.cend(), std::back_inserter(overlaps), [&](Group g)
		{
			auto overlap = FindOverlap(FindOverlap(g.a, g.b), g.c);

			return overlap[0];
		});

	return overlaps;
}

std::string Rucksacks::FindOverlap(std::string a, std::string b)
{
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());

	std::string intersection;
	std::set_intersection(a.begin(), a.end(),
		b.begin(), b.end(),
		std::back_inserter(intersection));

	return intersection;
}

int Rucksacks::FindTotalPriority(const std::string& priorities)
{
	return std::accumulate(priorities.cbegin(), priorities.cend(), 0, [&](int total, char c) 
		{
			if (InRange(c, 'a', 'z'))
				return total + c - 'a' + 1;
			else
				return total + c - 'A' + 27;
		});
}

void Rucksacks::Part1(const std::vector<Rucksack>& rucksacks)
{
	auto overlaps = FindOverlaps(rucksacks);
	auto totalPriority = FindTotalPriority(overlaps);

	std::cout << totalPriority << std::endl;
}

void Rucksacks::Part2(const std::vector<Rucksack>& rucksacks)
{
	auto groups = ParseGroups(rucksacks);
	auto overlaps = FindOverlaps(groups);
	auto totalPriority = FindTotalPriority(overlaps);

	std::cout << totalPriority << std::endl;
}
