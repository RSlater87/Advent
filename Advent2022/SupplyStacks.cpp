#include "SupplyStacks.h"
#include <regex>
#include "../AdventUtility/Utilities.h"
#include <iostream>

std::vector<std::list<char>> SupplyStacks::CrateMover9000(const std::string& filename)
{
	auto allText = ReadAllText(filename);
	auto allLines = SplitString(allText, "\n");

	std::regex startGrab(R"(\[[A-Z]\])");
	std::regex moveState("move [0-9]+ from [0-9]+ to [0-9]+");
	std::regex digitGrab(R"([0-9]+)");
	std::vector<std::list<char>> stacks;
	for (auto& line : allLines)
	{
		//initialise stacks if empty
		if (stacks.empty())
		{
			stacks = std::vector<std::list<char>>((line.size() + 1) / 4);
		}

		if (std::regex_search(line, startGrab))
		{
			std::string rest = line;
			std::smatch startMatch;
			size_t currentPos = 0;
			while (std::regex_search(rest, startMatch, startGrab))
			{
				auto position = (currentPos + startMatch.prefix().length()) / 4;
				stacks[position].push_back(startMatch[0].str()[1]);
				rest = startMatch.suffix();
				currentPos += startMatch.prefix().length() + startMatch[0].length();
			}
		}

		if (std::regex_match(line, moveState))
		{
			std::sregex_iterator iter(line.begin(), line.end(), digitGrab);
			auto quantity = std::stoi((*iter++)[0]);
			auto from = std::stoi((*iter++)[0]) - 1;
			auto to = std::stoi((*iter++)[0]) - 1;

			for (size_t index = 0; index < quantity; ++index)
			{
				if (stacks[from].empty())
					break;

				stacks[to].push_front(stacks[from].front());
				stacks[from].pop_front();
			}
		}
	}

	return stacks;
}

std::vector<std::list<char>> SupplyStacks::CrateMover9001(const std::string& filename)
{
	auto allText = ReadAllText(filename);
	auto allLines = SplitString(allText, "\n");

	std::regex startGrab(R"(\[[A-Z]\])");
	std::regex moveState("move [0-9]+ from [0-9]+ to [0-9]+");
	std::regex digitGrab(R"([0-9]+)");
	std::vector<std::list<char>> stacks;
	for (auto& line : allLines)
	{
		//initialise stacks if empty
		if (stacks.empty())
		{
			stacks = std::vector<std::list<char>>((line.size() + 1) / 4);
		}

		if (std::regex_search(line, startGrab))
		{
			std::string rest = line;
			std::smatch startMatch;
			size_t currentPos = 0;
			while (std::regex_search(rest, startMatch, startGrab))
			{
				auto position = (currentPos + startMatch.prefix().length()) / 4;
				stacks[position].push_back(startMatch[0].str()[1]);
				rest = startMatch.suffix();
				currentPos += startMatch.prefix().length() + startMatch[0].length();
			}
		}

		if (std::regex_match(line, moveState))
		{
			std::sregex_iterator iter(line.begin(), line.end(), digitGrab);
			auto quantity = std::stoi((*iter++)[0]);
			auto from = std::stoi((*iter++)[0]) - 1;
			auto to = std::stoi((*iter++)[0]) - 1;

			auto start = stacks[from].begin();
			auto end = stacks[from].begin();
			std::advance(end, quantity);

			stacks[to].splice(stacks[to].begin(), stacks[from], start, end);
		}
	}

	return stacks;
}

void SupplyStacks::PrintTopStacks(std::vector<std::list<char>> stack)
{
	std::string s;
	std::transform(stack.begin(), stack.end(), std::back_inserter(s), [&](std::list<char> l)
		{
			return l.front();
		});

	std::cout << s << std::endl;
}
