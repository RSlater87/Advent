#pragma once

#include <vector>
#include <list>
#include <string>

namespace SupplyStacks
{
	std::vector<std::list<char>> CrateMover9000(const std::string& filename);

	std::vector<std::list<char>> CrateMover9001(const std::string& filename);

	void PrintTopStacks(std::vector<std::list<char>> stack);
}