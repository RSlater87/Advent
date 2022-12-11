#pragma once

#include <string>
#include <vector>
#include <set>

struct Instruction
{
	std::string instruction;
	std::string argument;
};

class Emulator
{
public:
	Emulator();

	bool Execute(const std::vector<Instruction>& instructions);
	int GetAccumulator();

private:
	int m_accumulator_register;
	std::set<int> m_executed;
	std::vector<std::pair<int, Instruction>> m_instructions;
};

bool IsCorrupt(Instruction instruction);
Instruction Correction(Instruction instruction);

