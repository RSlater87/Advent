#pragma once

#include <string>

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