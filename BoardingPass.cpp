#include "BoardingPass.h"

BoardingPass ParseBoardingPass(const std::string& id)
{
	BoardingPass pass;
	pass.row = ParseRow(id.substr(0, 7));
	pass.column = ParseColumn(id.substr(7, 3));
	pass.SeatID = pass.row * 8 + pass.column;

	return pass;
}

bool CompareSeatId(const BoardingPass& a, const BoardingPass& b)
{
	return a.SeatID < b.SeatID;
}

int ParseRow(const std::string& row)
{
	int start = 0;
	int end = 127;
	int result = 0;
	for (auto& r : row)
	{
		int mid = (start + end) / 2;
		if (r == 'F')
		{
			end = mid;
			result = start;
		}
		else
		{
			start = mid + 1;
			result = end;
		}
	}

	return result;
}

int ParseColumn(const std::string& column)
{
	int start = 0;
	int end = 7;
	int result = 0;
	for (auto& c : column)
	{
		int mid = (start + end) / 2;
		if (c == 'L')
		{
			end = mid;
			result = start;
		}
		else
		{
			start = mid + 1;
			result = end;
		}
	}

	return result;
}