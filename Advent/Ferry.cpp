#include "Ferry.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <numeric>

std::vector<std::vector<Day11::FerryState>> Day11::ParseFile(const std::string& file)
{
	std::vector<std::string> lines = SplitString(ReadAllText(file), "\n");

	std::vector<std::vector<FerryState>> inputs;
	std::transform(lines.cbegin(), lines.cend(), std::back_inserter(inputs), [&](const std::string& line)
		{
			std::vector<FerryState> input;
			std::transform(line.cbegin(), line.cend(), std::back_inserter(input), [&](char c)
				{
					return c == 'L' ? FerryState::EmptySeat : FerryState::Floor;
				});
			return input;
		});

	return inputs;
}

void Day11::Part1(const std::vector<std::vector<FerryState>>& ferryTable)
{
	Timer t;

	auto current = ferryTable;

	//Iteratively loop through the rules to apply, checking the number of available seats each time
	//if seat count has stabilised then exit
	int occupiedSeats = 0;
	while (true)
	{
		//Rule #1: If a seat is empty and there are no occupied seats adjacent to it, the seat becomes occupied.
		current = SetEmptySeatsToOccupied_Part1(current);

		//Rule #2: If a seat is occupied and four or more seats adjacent to it are also occupied, the seat becomes empty.
		current = SetOccupiedSeatsToEmpty_Part1(current);

		//Check occupied seats and see if it has changed
		int currentOccupiedCount = GetOccupiedSeatsCount(current);

		if (currentOccupiedCount == occupiedSeats)
		{
			break;
		}

		occupiedSeats = currentOccupiedCount;
	}

	std::cout << occupiedSeats << std::endl;
}

void Day11::Part2(const std::vector<std::vector<FerryState>>& ferryTable)
{
	Timer t;

	auto current = ferryTable;

	//Iteratively loop through the rules to apply, checking the number of available seats each time
	//if seat count has stabilised then exit
	int occupiedSeats = 0;
	while (true)
	{
		//Rule #1: If a seat is empty and there are no occupied seats in view to it, the seat becomes occupied.
		current = SetEmptySeatsToOccupied_Part2(current);

		//Rule #2: If a seat is occupied and five or more seats in view to it are also occupied, the seat becomes empty.
		current = SetOccupiedSeatsToEmpty_Part2(current);

		//Check occupied seats and see if it has changed
		int currentOccupiedCount = GetOccupiedSeatsCount(current);

		if (currentOccupiedCount == occupiedSeats)
		{
			break;
		}

		occupiedSeats = currentOccupiedCount;
	}

	std::cout << occupiedSeats << std::endl;
}

std::vector<std::vector<Day11::FerryState>> Day11::SetEmptySeatsToOccupied_Part1(const std::vector<std::vector<FerryState>>& ferryTable)
{
	std::vector<std::vector<FerryState>> updateTable = ferryTable;

	const size_t rows = ferryTable.size();
	for (size_t row = 0; row < rows; ++row)
	{
		const size_t cols = ferryTable[row].size();
		for (size_t col = 0; col < cols; ++col)
		{
			if (GetState(ferryTable, rows, cols, row, col) != FerryState::EmptySeat)
			{
				continue;
			}

			if (GetState(ferryTable, rows, cols, row - 1, col) == FerryState::OccupiedSeat
				|| GetState(ferryTable, rows, cols, row - 1, col + 1) == FerryState::OccupiedSeat
				|| GetState(ferryTable, rows, cols, row, col + 1) == FerryState::OccupiedSeat
				|| GetState(ferryTable, rows, cols, row + 1, col + 1) == FerryState::OccupiedSeat
				|| GetState(ferryTable, rows, cols, row + 1, col) == FerryState::OccupiedSeat
				|| GetState(ferryTable, rows, cols, row + 1, col - 1) == FerryState::OccupiedSeat
				|| GetState(ferryTable, rows, cols, row, col - 1) == FerryState::OccupiedSeat
				|| GetState(ferryTable, rows, cols, row - 1, col - 1) == FerryState::OccupiedSeat)
			{
				continue;
			}

			updateTable[row][col] = FerryState::OccupiedSeat;
		}
	}

	return updateTable;
}

std::vector<std::vector<Day11::FerryState>> Day11::SetOccupiedSeatsToEmpty_Part1(const std::vector<std::vector<FerryState>>& ferryTable)
{
	std::vector<std::vector<FerryState>> updateTable = ferryTable;

	const size_t rows = ferryTable.size();
	for (size_t row = 0; row < rows; ++row)
	{
		const size_t cols = ferryTable[row].size();
		for (size_t col = 0; col < cols; ++col)
		{
			if (GetState(ferryTable, rows, cols, row, col) != FerryState::OccupiedSeat)
			{
				continue;
			}
			
			int count = 0;
			if (count >= 4 || GetState(ferryTable, rows, cols, row - 1, col) == FerryState::OccupiedSeat) count++;
			if (count >= 4 || GetState(ferryTable, rows, cols, row - 1, col + 1) == FerryState::OccupiedSeat) count++;
			if (count >= 4 || GetState(ferryTable, rows, cols, row, col + 1) == FerryState::OccupiedSeat) count++;
			if (count >= 4 || GetState(ferryTable, rows, cols, row + 1, col + 1) == FerryState::OccupiedSeat) count++;
			if (count >= 4 || GetState(ferryTable, rows, cols, row + 1, col) == FerryState::OccupiedSeat) count++;
			if (count >= 4 || GetState(ferryTable, rows, cols, row + 1, col - 1) == FerryState::OccupiedSeat) count++;
			if (count >= 4 || GetState(ferryTable, rows, cols, row, col - 1) == FerryState::OccupiedSeat) count++;
			if (count >= 4 || GetState(ferryTable, rows, cols, row - 1, col - 1) == FerryState::OccupiedSeat) count++;

			if(count >= 4)
			{
				updateTable[row][col] = FerryState::EmptySeat;
			}
		}
	}

	return updateTable;
}

std::vector<std::vector<Day11::FerryState>> Day11::SetEmptySeatsToOccupied_Part2(const std::vector<std::vector<FerryState>>& ferryTable)
{
	std::vector<std::vector<FerryState>> updateTable = ferryTable;

	const size_t rows = ferryTable.size();
	for (size_t row = 0; row < rows; ++row)
	{
		const size_t cols = ferryTable[row].size();
		for (size_t col = 0; col < cols; ++col)
		{
			if (GetState(ferryTable, rows, cols, row, col) != FerryState::EmptySeat)
			{
				continue;
			}

			if (FindInDirection(ferryTable, rows, cols, row - 1, col, -1, 0, FerryState::OccupiedSeat)
				|| FindInDirection(ferryTable, rows, cols, row - 1, col + 1, -1, 1, FerryState::OccupiedSeat)
				|| FindInDirection(ferryTable, rows, cols, row, col + 1, 0, 1, FerryState::OccupiedSeat)
				|| FindInDirection(ferryTable, rows, cols, row + 1, col + 1, 1, 1, FerryState::OccupiedSeat)
				|| FindInDirection(ferryTable, rows, cols, row + 1, col, 1, 0, FerryState::OccupiedSeat)
				|| FindInDirection(ferryTable, rows, cols, row + 1, col - 1, 1, -1, FerryState::OccupiedSeat)
				|| FindInDirection(ferryTable, rows, cols, row, col - 1, 0, -1, FerryState::OccupiedSeat)
				|| FindInDirection(ferryTable, rows, cols, row - 1, col - 1, -1, -1, FerryState::OccupiedSeat))
			{
				continue;
			}

			updateTable[row][col] = FerryState::OccupiedSeat;
		}
	}

	return updateTable;
}

std::vector<std::vector<Day11::FerryState>> Day11::SetOccupiedSeatsToEmpty_Part2(const std::vector<std::vector<FerryState>>& ferryTable)
{
	std::vector<std::vector<FerryState>> updateTable = ferryTable;

	const size_t rows = ferryTable.size();
	for (size_t row = 0; row < rows; ++row)
	{
		const size_t cols = ferryTable[row].size();
		for (size_t col = 0; col < cols; ++col)
		{
			if (GetState(ferryTable, rows, cols, row, col) != FerryState::OccupiedSeat)
			{
				continue;
			}

			int count = 0;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row - 1, col, -1, 0, FerryState::OccupiedSeat)) count++;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row - 1, col + 1, -1, 1, FerryState::OccupiedSeat)) count++;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row, col + 1, 0, 1, FerryState::OccupiedSeat)) count++;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row + 1, col + 1, 1, 1, FerryState::OccupiedSeat)) count++;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row + 1, col, 1, 0, FerryState::OccupiedSeat)) count++;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row + 1, col - 1, 1, -1, FerryState::OccupiedSeat)) count++;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row, col - 1, 0, -1, FerryState::OccupiedSeat)) count++;
			if (count >= 5 || FindInDirection(ferryTable, rows, cols, row - 1, col - 1, -1, -1, FerryState::OccupiedSeat)) count++;

			if (count >= 5)
			{
				updateTable[row][col] = FerryState::EmptySeat;
			}
		}
	}

	return updateTable;
}

int Day11::GetOccupiedSeatsCount(const std::vector<std::vector<FerryState>>& ferryTable)
{
	return std::accumulate(ferryTable.cbegin(), ferryTable.cend(), 0, [&](int runningTotal, const std::vector<FerryState>& row)
		{
			return runningTotal + (int)std::count(row.cbegin(), row.cend(), FerryState::OccupiedSeat);
		});
}

Day11::FerryState Day11::GetState(const std::vector<std::vector<FerryState>>& ferryTable, size_t rows, size_t cols, size_t row, size_t col)
{
	if (InRange(row, size_t{ 0 }, rows - 1) && InRange(col, size_t{ 0 }, cols - 1))
	{
		return ferryTable[row][col];
	}

	return FerryState::OutBounds; //just flag as 
}

bool Day11::FindInDirection(const std::vector<std::vector<FerryState>>& ferryTable, size_t rows, size_t cols, size_t row, size_t col, int x, int y, FerryState toFind)
{
	if (!InRange(row, size_t{ 0 }, rows - 1) || !InRange(col, size_t{ 0 }, cols - 1))
	{
		//Out of bounds, so couldn't find target = return false
		return false;
	}

	if (ferryTable[row][col] == toFind)
	{
		return true;
	}

	//If we've hit a obscuring state before finding out target, return false
	if (ferryTable[row][col] != FerryState::Floor)
	{
		return false;
	}

	//Otherwise look further on
	return FindInDirection(ferryTable, rows, cols, row + x, col + y, x, y, toFind);
}