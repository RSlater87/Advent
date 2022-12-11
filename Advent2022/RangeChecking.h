#pragma once

#include <utility>
#include <vector>
#include <string>

namespace RangeChecking
{
	typedef std::pair<std::pair<int, int>, std::pair<int, int>> ElfSchedule;

	std::vector<ElfSchedule> ParseInputs(const std::string& filename);

	int FindTotalOverlap(const std::vector<ElfSchedule>& elfSchedules);
	int FindPartialOverlap(const std::vector<ElfSchedule>& elfSchedules);

	void Part1(std::vector<ElfSchedule>& elfSchedules);

	void Part2(std::vector<ElfSchedule>& elfSchedules);
}