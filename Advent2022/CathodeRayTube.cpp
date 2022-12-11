#include "CathodeRayTube.h"

#include "../AdventUtility/Utilities.h"
#include <iostream>
#include <array>

void CathodeRayTube::Part1(const std::string& filename)
{
	auto allLines = SplitString(ReadAllText(filename), "\n");

	int x = 1;
	std::vector<int> xHistory = { x }; // secret 0th cycle
	int cycle = 0;
	std::array<char, 240> screen;
	screen.fill('.');

	for (auto line : allLines)
	{
		if (line == "noop")
		{
			//Do nothing
			if (InRange(cycle % 40, x - 1, x + 1))
			{
				screen[cycle] = '#';
			}
			xHistory.push_back(x);
			cycle++;
		}
		else
		{
			if (InRange(cycle % 40, x - 1, x + 1))
			{
				screen[cycle] = '#';
			}
			auto parts = SplitString(line, " ");
			xHistory.push_back(x);
			cycle++;

			if (InRange(cycle % 40, x - 1, x + 1))
			{
				screen[cycle] = '#';
			}
			x += std::stoi(parts[1]);
			xHistory.push_back(x);
			cycle++;
		}
	}

	int sum = 0;
	for (int i = 19; i < xHistory.size(); i += 40)
	{
		std::cout << xHistory[i] * (i + 1) << " + ";
		sum += xHistory[i] * (i + 1);
	}

	std::cout << " = " << sum << std::endl;

	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 40; col++)
		{
			std::cout << screen[row * 40 + col];
		}
		std::cout << std::endl;
	}
}
