#include "Customs.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <chrono>
#include <numeric>

std::vector<Day6::Customs> Day6::ParseFile(const std::string& file)
{
	std::vector<Customs> inputs;
	std::fstream fs;
	fs.open(file);

	std::vector<std::string> groups;
	while (fs.good())
	{
		std::string line;
		std::getline(fs, line);
		if (!line.empty())
		{
			groups.push_back(line);
		}
		else
		{
			Customs cs = { groups };
			inputs.push_back(cs);
			groups.clear();
		}
	}

	return inputs;
}

void Day6::Part1(const std::vector<Customs>& inputs)
{
	auto start = std::chrono::system_clock::now();
	std::vector<size_t> combinedStringSizes;

	//Anyone answered = get distinct string
	std::transform(inputs.cbegin(), inputs.cend(), std::back_inserter(combinedStringSizes), [&](const Customs& cs)
		{
			//Sort lines from the group string
			std::vector<std::string> lines = cs.lines;
			for (auto& a : lines)
			{
				std::sort(a.begin(), a.end());
			}

			//Find union beetween each set
			std::string intersection = lines[0];
			for (auto line = lines.cbegin() + 1; line != lines.cend(); ++line)
			{
				std::string intersect;
				std::set_union(intersection.cbegin(), intersection.cend(),
					line->cbegin(), line->cend(),
					std::back_inserter(intersect));
				intersection = intersect;
			}

			//return the size of the distinct string
			return intersection.size();
		});

	//Get total count
	size_t totalCustoms = std::accumulate(combinedStringSizes.cbegin(), combinedStringSizes.cend(), size_t{ 0 });

	std::cout << totalCustoms << std::endl;
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

void Day6::Part2(const std::vector<Customs>& inputs)
{
	auto start = std::chrono::system_clock::now();
	std::vector<size_t> combinedStringSizes;

	//Everyone answered = get intersection string from the lines
	std::transform(inputs.cbegin(), inputs.cend(), std::back_inserter(combinedStringSizes), [&](const Customs& cs)
		{
			//Sort lines from the group string
			std::vector<std::string> lines = cs.lines;
			for (auto& a : lines)
			{
				std::sort(a.begin(), a.end());
			}

			//Find the intersection between each set
			std::string intersection = lines[0];
			for (auto line = lines.cbegin() + 1; line != lines.cend(); ++line)
			{
				std::string intersect;
				std::set_intersection(intersection.cbegin(), intersection.cend(),
					line->cbegin(), line->cend(),
					std::back_inserter(intersect));
				intersection = intersect;
			}

			//return the size of the overall intersection
			return intersection.size();
		});

	//Get total count
	size_t totalCustoms = std::accumulate(combinedStringSizes.cbegin(), combinedStringSizes.cend(), size_t{ 0 });

	std::cout << totalCustoms << std::endl;
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}