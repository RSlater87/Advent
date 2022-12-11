#pragma once

#include <string>
#include <vector>

namespace Day11
{
	enum class FerryState
	{
		OutBounds,
		EmptySeat,
		Floor,
		OccupiedSeat
	};

	std::vector<std::vector<FerryState>> ParseFile(const std::string& file);
	void Part1(const std::vector<std::vector<FerryState>>& ferryTable);

	std::vector<std::vector<FerryState>> SetEmptySeatsToOccupied_Part1(const std::vector<std::vector<FerryState>>& ferryTable);
	std::vector<std::vector<FerryState>> SetOccupiedSeatsToEmpty_Part1(const std::vector<std::vector<FerryState>>& ferryTable);

	void Part2(const std::vector<std::vector<FerryState>>& ferryTable);
	std::vector<std::vector<FerryState>> SetEmptySeatsToOccupied_Part2(const std::vector<std::vector<FerryState>>& ferryTable);
	std::vector<std::vector<FerryState>> SetOccupiedSeatsToEmpty_Part2(const std::vector<std::vector<FerryState>>& ferryTable);

	int GetOccupiedSeatsCount(const std::vector<std::vector<FerryState>>& ferryTable);

	FerryState GetState(const std::vector<std::vector<FerryState>>& ferryTable, size_t rows, size_t cols, size_t row, size_t col);
	bool FindInDirection(const std::vector<std::vector<FerryState>>& ferryTable, size_t rows, size_t cols, size_t row, size_t col, int x, int y, FerryState toFind);
}