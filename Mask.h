#pragma once

#include <vector>
#include <string>
#include <bitset>

namespace Day14
{
	struct MaskInstruction
	{
		std::string instruction;
		std::string argument;
	};

	struct Mask
	{
		std::bitset<36> on;
		std::bitset<36> off;
	};

	std::vector<MaskInstruction> ParseFile(const std::string& file);

	void Part1(const std::vector<MaskInstruction>& inputs);
	void Part2(const std::vector<MaskInstruction>& inputs);
}