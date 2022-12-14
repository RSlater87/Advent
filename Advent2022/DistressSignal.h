#pragma once

#include <string>

namespace DistressSignal
{
	int Part1_ParseAndCompare(const std::string& filename);

	bool ArePacketsInOrder(const std::string& lhs, const std::string& rhs);
}