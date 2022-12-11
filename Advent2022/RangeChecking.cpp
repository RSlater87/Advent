#include "RangeChecking.h"

#include "../AdventUtility/Utilities.h"
#include <iostream>
#include <fstream>

std::vector<RangeChecking::ElfSchedule> RangeChecking::ParseInputs(const std::string& filename)
{
	std::ifstream is{ filename };

	if (!is)
	{
		return {};
	}

	char dummy;
	std::vector<RangeChecking::ElfSchedule> elfSchedules;
	ElfSchedule elfSchedule;
	while (is >> elfSchedule.first.first >> dummy >> elfSchedule.first.second >> dummy
		>> elfSchedule.second.first >> dummy >> elfSchedule.second.second)
	{
		elfSchedules.push_back(elfSchedule);
	}

	return elfSchedules;
}

int RangeChecking::FindTotalOverlap(const std::vector<ElfSchedule>& elfSchedules)
{
	std::vector<ElfSchedule> overlaps;

	std::copy_if(elfSchedules.cbegin(), elfSchedules.cend(), std::back_inserter(overlaps), [&](const ElfSchedule elfSchedule)
		{
			return (elfSchedule.first.first <= elfSchedule.second.first && elfSchedule.first.second >= elfSchedule.second.second)	//(A <= X && B >= Y)
				|| (elfSchedule.second.first <= elfSchedule.first.first && elfSchedule.second.second >= elfSchedule.first.second);	//(X <= A && Y >= B)
		});

	return (int)overlaps.size();
}

int RangeChecking::FindPartialOverlap(const std::vector<ElfSchedule>& elfSchedules)
{
	std::vector<ElfSchedule> overlaps;

	std::copy_if(elfSchedules.cbegin(), elfSchedules.cend(), std::back_inserter(overlaps), [&](const ElfSchedule elfSchedule)
		{
			return (elfSchedule.first.first <= elfSchedule.second.first && elfSchedule.first.second >= elfSchedule.second.first)	//(A <= X && B >= X)
				|| (elfSchedule.first.first <= elfSchedule.second.second && elfSchedule.first.second >= elfSchedule.second.second)	//(A <= Y && B >= Y)
				|| (elfSchedule.second.first <= elfSchedule.first.first && elfSchedule.second.second >= elfSchedule.first.first)	//(X <= A && Y >= A)
				|| (elfSchedule.second.first <= elfSchedule.first.second && elfSchedule.second.second >= elfSchedule.first.second); //(X <= B && Y >= B)
		});

	return (int)overlaps.size();
}

void RangeChecking::Part1(std::vector<ElfSchedule>& elfSchedules)
{
	std::cout << FindTotalOverlap(elfSchedules) << std::endl;
}

void RangeChecking::Part2(std::vector<ElfSchedule>& elfSchedules)
{
	std::cout << FindPartialOverlap(elfSchedules) << std::endl;
}
