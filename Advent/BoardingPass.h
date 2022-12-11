#pragma once

#include <string>
#include <vector>

namespace Day5
{
	struct BoardingPass
	{
		int row;
		int column;
		int SeatID;
	};

	bool CompareSeatId(const BoardingPass& a, const BoardingPass& b);

	BoardingPass ParseBoardingPass(const std::string& id);
	int ParseRow(const std::string& row);
	int ParseColumn(const std::string& column);

	std::vector<BoardingPass> ParseFile(const std::string& file);
	void Part1(const std::vector<BoardingPass>& inputs);
	void Part2(const std::vector<BoardingPass>& inputs);
}