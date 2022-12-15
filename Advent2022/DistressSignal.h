#pragma once

#include <string>

namespace DistressSignal
{
	void Part1(const std::string& filename);

	void Part2(const std::string& filename);

	enum class State
	{
		InOrder,
		ContinueParsing,
		OutOfOrder
	};

	State ArePacketsInOrder(std::string lhs, std::string rhs);

	std::string::const_iterator FindSubList(std::string::const_iterator start, std::string::const_iterator end);

	std::string::const_iterator FindAndExtractSubList(std::string::const_iterator start, std::string::const_iterator end, std::string& substr);

	std::string::const_iterator FindAndExtractNumber(std::string::const_iterator start, std::string::const_iterator end, std::string& substr);
}