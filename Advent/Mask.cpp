#include "Mask.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <chrono>
#include <numeric>
#include <bitset>
#include <map>

std::vector<Day14::MaskInstruction> Day14::ParseFile(const std::string& file)
{
	std::vector<std::string> lines = SplitString(ReadAllText(file), "\n");

	std::vector<Day14::MaskInstruction> inputs;
	std::transform(lines.cbegin(), lines.cend(), std::back_inserter(inputs), [&](const std::string& line)
		{
			auto parts = SplitString(line, " = ");
			return MaskInstruction{ parts[0], parts[1] };
		});

	return inputs;
}

void Day14::Part1(const std::vector<MaskInstruction>& inputs)
{
	Timer t;

	Mask mask;
	std::map<std::string, int64_t> memory;

	for (auto& instruction : inputs)
	{
		if (instruction.instruction == "mask")
		{
			std::string on_pattern = instruction.argument;
			std::string off_pattern = instruction.argument;
			std::replace(on_pattern.begin(), on_pattern.end(), 'X', '0');
			std::replace(off_pattern.begin(), off_pattern.end(), 'X', '1');
			mask.on = std::bitset<36>{ on_pattern };
			mask.off = std::bitset<36>{ off_pattern };
		}
		else
		{
			//Apply mask onto argument;
			int64_t value = std::stoi(instruction.argument);
			value = value | mask.on.to_ullong();
			value = value & mask.off.to_ullong();

			memory[instruction.instruction] = value;
		}
	}

	int64_t total = std::accumulate(memory.cbegin(), memory.cend(), int64_t{ 0 }, [&](int64_t total, std::pair<std::string, int64_t> kvp)
		{
			return total + kvp.second;
		});

	std::cout << total << std::endl;
}

void Day14::Part2(const std::vector<MaskInstruction>& inputs)
{
	Timer t;
	std::string mask;
	std::map<int64_t, int64_t> memory;
	for (auto& instruction : inputs)
	{
		if (instruction.instruction == "mask")
		{
			mask = instruction.argument;
		}
		else
		{
			//Get original address out of instruction
			std::string inst = instruction.instruction;
			int64_t value = std::stoi(instruction.argument);
			std::replace(inst.begin(), inst.end(), '[', ' ');
			std::replace(inst.begin(), inst.end(), ']', ' ');
			auto parts = SplitString(inst);
			int64_t address = std::stoi(parts[1]);

			//Apply mask onto address in instruction;
			std::string base_mask = mask;
			std::replace(base_mask.begin(), base_mask.end(), 'X', '0');
			std::bitset<36> on{ base_mask };
			std::bitset<36> base_address = address | on.to_ullong();

			//Apply floating bits
			std::string floating_mask = mask;
			std::vector<std::bitset<36>> addresses{ base_address };
			auto pos = floating_mask.find('X');
			while (pos != std::string::npos)
			{
				auto offset = floating_mask.size() - pos - 1;
				std::vector<std::bitset<36>> inner_addresses;
				for (auto& address : addresses)
				{
					auto address_on = address;
					address_on.set(offset, true);
					auto address_off = address;
					address_off.set(offset, false);

					inner_addresses.push_back(address_on);
					inner_addresses.push_back(address_off);
				}
				addresses = inner_addresses;
				floating_mask[pos] = '0';
				pos = floating_mask.find('X');
			}

			for (auto& address : addresses)
			{
				memory[address.to_ullong()] = value;
			}
		}
	}

	int64_t total = std::accumulate(memory.cbegin(), memory.cend(), int64_t{ 0 }, [&](int64_t total, std::pair<int64_t, int64_t> kvp)
		{
			return total + kvp.second;
		});

	std::cout << total << std::endl;
}