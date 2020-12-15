#include "Customs.h"
#include "Utilities.h"
#include "Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>

std::vector<std::string> Day6::ParseFile(const std::string& file)
{
	std::vector<std::string> inputs = SplitString(ReadAllText(file), "\n\n");

	return inputs;
}

void Day6::Part1(const std::vector<std::string>& inputs)
{
	Timer t;
	std::vector<size_t> combinedStringSizes;

	//Anyone answered = get distinct string
	std::transform(inputs.cbegin(), inputs.cend(), std::back_inserter(combinedStringSizes), [&](const std::string& cs)
		{
			//Sort lines from the group string
			std::vector<std::string> lines = SplitString(cs, "\n");
			for (auto& a : lines)
			{
				std::sort(a.begin(), a.end());
			}

			//Find union between each set
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
}

void Day6::Part2(const std::vector<std::string>& inputs)
{
	Timer t;
	std::vector<size_t> combinedStringSizes;

	//Everyone answered = get intersection string from the lines
	std::transform(inputs.cbegin(), inputs.cend(), std::back_inserter(combinedStringSizes), [&](const std::string& cs)
		{
			//Sort lines from the group string
			std::vector<std::string> lines = SplitString(cs, "\n");
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
}