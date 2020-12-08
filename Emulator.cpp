#include "Emulator.h"

namespace Instructions
{
	const std::string NOP = "nop";
	const std::string JMP = "jmp";
	const std::string ACC = "acc";
}

Emulator::Emulator()
{
}

bool Emulator::Execute(const std::vector<Instruction>& instructions)
{
	m_executed.clear();
	m_instructions.clear();
	m_accumulator_register = 0;

	for (auto index = 0; index < instructions.size(); ++index)
	{
		auto current = instructions[index];
		auto insert = m_executed.insert(index);
		if (!insert.second)
		{
			//Failed to insert, so this instruction has already been executed
			return false;
		}
		m_instructions.push_back(std::make_pair(index, current));
			
		if (current.instruction == Instructions::NOP)
		{
			continue;
		}
		else if (current.instruction == Instructions::JMP)
		{
			index += std::stoi(current.argument) - 1; //take increment into account
		}
		else if (current.instruction == Instructions::ACC)
		{
			m_accumulator_register += std::stoi(current.argument);
		}
	}

	return true;
}

int Emulator::GetAccumulator()
{
	return m_accumulator_register;
}

bool IsCorrupt(Instruction instruction)
{
	return instruction.instruction == Instructions::JMP
		|| instruction.instruction == Instructions::NOP;
}

Instruction Correction(Instruction instruction)
{
	if (instruction.instruction == Instructions::JMP)
	{
		instruction.instruction = Instructions::NOP;
	}
	else if (instruction.instruction == Instructions::NOP)
	{
		instruction.instruction = Instructions::JMP;
	}

	return instruction;
}

