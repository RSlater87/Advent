#include "GameConsole.h"
#include "Utilities.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <chrono>
#include <numeric>

std::vector<Instruction> Day8::ParseFile(const std::string& file)
{
	std::vector<std::string> inputs = SplitString(ReadAllText(file), "\n");
	std::vector<Instruction> instructions;
	for (auto input : inputs)
	{
		if (input.empty())
		{
			continue;
		}

		auto parts = SplitString(input, ' ');

		instructions.emplace_back(Instruction{ parts[0], parts[1] });
	}

	return instructions;
}

void Day8::Part1(const std::vector<Instruction>& instructions)
{
	auto start = std::chrono::system_clock::now();

	Emulator emulator;
	emulator.Execute(instructions);
	std::cout << emulator.GetAccumulator() << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

void Day8::Part2(const std::vector<Instruction>& instructions)
{
	auto start = std::chrono::system_clock::now();

	//Use a brute-force approach to determine which instruction to change
	//This can be made more efficient if we make a graph of the instruction set and work out how to join the end-goal
	//by looking at possible changes to the corrupt instructions
	Emulator emulator;
	std::vector<Instruction> copy_instructions;
	auto possible_corrupt = instructions.cbegin();

	do
	{
		possible_corrupt = std::find_if(possible_corrupt, instructions.cend(), IsCorrupt);
		auto index = std::distance(instructions.cbegin(), possible_corrupt);
		copy_instructions = instructions;
		copy_instructions[index] = Correction(*possible_corrupt);
		possible_corrupt++; //check the instructions after this iterator next

	} while (!emulator.Execute(copy_instructions));

	std::cout << emulator.GetAccumulator() << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}