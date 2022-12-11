#pragma once

#include <string>
#include <vector>
#include <map>

namespace Day16
{
	struct TicketRule
	{
		std::string name;
		std::pair<int, int> rangeLeft;
		std::pair<int, int> rangeRight;
	};

	std::vector<TicketRule> ParseRules(const std::string& file);

	struct Tickets
	{
		std::vector<int> myTicket;
		std::vector<std::vector<int>> nearbyTickets;
	};

	Tickets ParseTickets(const std::string& myTicketPath, const std::string& nearbyTicketPath);

	bool IsNumberValid(int num, TicketRule rule);

	void Part1(const std::vector<TicketRule>& rules, Tickets tickets);

	void Part2(const std::vector<TicketRule>& rules, Tickets tickets);
}