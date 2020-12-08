#pragma once
#include <string>
#include <vector>

#include "Emulator.h"

namespace Day8
{
	std::vector<Instruction> ParseFile(const std::string& file);

	void Part1(const std::vector<Instruction>& instructions);
	void Part2(const std::vector<Instruction>& instructions);
}