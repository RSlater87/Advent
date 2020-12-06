#pragma once

#include <string>
#include <vector>

namespace Day6
{
	struct Customs
	{
		std::vector<std::string> lines;
		//std::string group;
	};

	std::vector<Customs> ParseFile(const std::string& file);
	void Part1(const std::vector<Customs>& inputs);
	void Part2(const std::vector<Customs>& inputs);
}