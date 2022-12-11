#include "TrainTicket.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <numeric>

std::vector<Day16::TicketRule> Day16::ParseRules(const std::string& file)
{
	std::vector<std::string> lines = SplitString(ReadAllText(file), "\r\n");
	std::vector<Day16::TicketRule> rules;
	for (auto& line : lines)
	{
		auto parts = SplitString(line, ": ");
		auto ranges = SplitString(parts[1], " or ");
		auto left = SplitString(ranges[0], "-");
		auto right = SplitString(ranges[1], "-");

		TicketRule rule;
		rule.name = parts[0];
		rule.rangeLeft = std::make_pair(std::stoi(left[0]), std::stoi(left[1]));
		rule.rangeRight = std::make_pair(std::stoi(right[0]), std::stoi(right[1]));

		rules.push_back(rule);
	}

	return rules;
}

Day16::Tickets Day16::ParseTickets(const std::string& myTicketPath, const std::string& nearbyTicketPath)
{
	Tickets tickets;

	std::vector<std::string> myTicket = SplitString(ReadAllText(myTicketPath), ",");
	std::transform(myTicket.cbegin(), myTicket.cend(), std::back_inserter(tickets.myTicket), [&](const std::string& num)
		{
			return std::stoi(num);
		});

	std::vector<std::string> lines = SplitString(ReadAllText(nearbyTicketPath), "\r\n");
	std::transform(lines.cbegin(), lines.cend(), std::back_inserter(tickets.nearbyTickets), [&](const std::string& nums)
		{
			std::vector<std::string> nearbyTicket = SplitString(nums, ",");
			std::vector<int> ticket;
			std::transform(nearbyTicket.cbegin(), nearbyTicket.cend(), std::back_inserter(ticket), [&](const std::string& num)
				{
					return std::stoi(num);
				});
			return ticket;
		});

	return tickets;
}

bool Day16::IsNumberValid(int num, TicketRule rule)
{
	return InRange(num, rule.rangeLeft.first, rule.rangeLeft.second)
		|| InRange(num, rule.rangeRight.first, rule.rangeRight.second);
}

void Day16::Part1(const std::vector<TicketRule>& rules, Tickets tickets)
{
	Timer t;

	//work out which values in the nearby tickets are not valid for any rule
	int64_t errorRate = 0;
	for (auto& ticket : tickets.nearbyTickets)
	{
		for (auto& value : ticket)
		{
			bool allRulesBroken = std::all_of(rules.cbegin(), rules.cend(), [&](const TicketRule& rule)
				{
					return !IsNumberValid(value, rule);
				});

			if (allRulesBroken)
			{
				errorRate += value;
			}
		}
	}

	std::cout << errorRate << std::endl;
}

void Day16::Part2(const std::vector<TicketRule>& rules, Tickets tickets)
{
	//Remove invalid tickets
	std::vector<std::vector<int>> validTickets;
	std::copy_if(tickets.nearbyTickets.cbegin(), tickets.nearbyTickets.cend(), std::back_inserter(validTickets), [&](const std::vector<int>& ticket)
		{
			bool allNumbersObeyRules = std::all_of(ticket.cbegin(), ticket.cend(), [&](int num)
				{
					bool allRulesCorrect = std::any_of(rules.cbegin(), rules.cend(), [&](const TicketRule& rule)
						{
							return IsNumberValid(num, rule);
						});
					return allRulesCorrect;
				});
			return allNumbersObeyRules;
		});

	//Go column by column and work out the rule which all of the values in the column obey
	//eliminate that rule from the running each time
	std::vector<TicketRule> possibleRules = rules;
	std::map<std::string, size_t> mapOfRuleToColumns;

	for (size_t index = 0; index < validTickets[0].size(); ++index)
	{
		std::vector<TicketRule> matchingRules;
		std::copy_if(possibleRules.cbegin(), possibleRules.cend(), std::back_inserter(matchingRules), [&](const TicketRule& rule)
			{
				for (size_t row = 0; row < validTickets.size(); ++row)
				{
					if (!IsNumberValid(validTickets[row][index], rule))
					{
						return false;
					}
				}

				return true;
			});

		if (matchingRules.size() > 1)
		{
			std::cout << "Oops" << std::endl;
		}

		mapOfRuleToColumns[matchingRules[0].name] = index;
		possibleRules.erase(std::remove_if(possibleRules.begin(), possibleRules.end(), [&](TicketRule& rule)
			{
				return rule.name == matchingRules[0].name;
			}));
	}

	int64_t product = 1;
	for (auto& kvp : mapOfRuleToColumns)
	{
		if (kvp.first.find("destination") != std::string::npos)
		{
			product *= kvp.second;
		}
	}

	std::cout << product << std::endl;
}