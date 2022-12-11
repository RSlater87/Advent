#include "BoardingPass.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>

Day5::BoardingPass Day5::ParseBoardingPass(const std::string& id)
{
	BoardingPass pass;
	pass.row = ParseRow(id.substr(0, 7));
	pass.column = ParseColumn(id.substr(7, 3));
	pass.SeatID = pass.row * 8 + pass.column;

	return pass;
}

bool Day5::CompareSeatId(const BoardingPass& a, const BoardingPass& b)
{
	return a.SeatID < b.SeatID;
}

int Day5::ParseRow(const std::string& row)
{
	std::vector<bool> flags;
	std::transform(row.cbegin(), row.cend(), std::back_inserter(flags), [](char c) { return c == 'F'; });

	return BinarySpacePartition(flags);
}

int Day5::ParseColumn(const std::string& column)
{
	std::vector<bool> flags;
	std::transform(column.cbegin(), column.cend(), std::back_inserter(flags), [](char c) { return c == 'L'; });

	return BinarySpacePartition(flags);
}

std::vector<Day5::BoardingPass> Day5::ParseFile(const std::string& file)
{
	std::vector<BoardingPass> inputs;
	std::fstream fs;
	fs.open(file);

	while (fs.good())
	{
		std::string line;
		std::getline(fs, line);
		if (!line.empty())
		{
			inputs.push_back(ParseBoardingPass(line));
		}
	}

    return inputs;
}

void Day5::Part1(const std::vector<BoardingPass>& inputs)
{
    Timer t;
	auto max = std::max_element(inputs.cbegin(), inputs.cend(), CompareSeatId);
	std::cout << (*max).SeatID << std::endl;
}

void Day5::Part2(const std::vector<BoardingPass>& inputs)
{
    {
        Timer t;

        //Sort the boarding passes by Seat ID
        auto sortedInputs = inputs;
        std::sort(sortedInputs.begin(), sortedInputs.end(), CompareSeatId);

        //Find missing seat IDs using lower bound
        for (int i = 68; i < 965; ++i)
        {
            auto lower = std::lower_bound(sortedInputs.begin(), sortedInputs.end(), i, [&](const BoardingPass& p, int i)
                {
                    return p.SeatID < i;
                });

            if (lower != sortedInputs.cend() && lower->SeatID != i)
            {
                //Couldn't find i
                std::cout << "Missing: " << i << std::endl;
            }
        }
    }

    {
        Timer t;

        //Find missing seat IDs using lower bound
        for (int i = 68; i < 965; ++i)
        {
            auto lower = std::find_if(inputs.begin(), inputs.end(), [&](const BoardingPass& p)
                {
                    return p.SeatID == i;
                });

            if (lower == inputs.cend())
            {
                //Couldn't find i
                std::cout << "Missing: " << i << std::endl;
            }
        }
    }
}