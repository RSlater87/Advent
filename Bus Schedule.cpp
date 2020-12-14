﻿#include "BusSchedule.h"

#include "Utilities.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <chrono>
#include <numeric>

Day13::BusSchedule Day13::ParseFile(const std::string& file)
{
	std::vector<std::string> lines = SplitString(ReadAllText(file), "\n");

	BusSchedule bs;
	bs.target = std::stoi(lines[0]);

	auto buses = SplitString(lines[1], ',');
	for (int64_t i = 0; i < buses.size(); ++i)
	{
		if (buses[i] != "x")
		{
			int64_t num = std::stoi(buses[i]);
			int64_t remainder = num - (i % num);

			bs.buses.push_back(num);
			bs.remainders.push_back(remainder);
		}
	}


	return bs;
}

void Day13::Part1(BusSchedule bs)
{
	auto start = std::chrono::system_clock::now();

	auto nearest = *std::min_element(bs.buses.cbegin(), bs.buses.cend(), [&](int64_t a, int64_t b)
		{
			return a - (bs.target % a) < b - (bs.target % b);
		});

	std::cout << nearest * (nearest - bs.target % nearest) << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

void Day13::Part2(BusSchedule bs)
{
	auto start = std::chrono::system_clock::now();

	int64_t answer = MinimumCommonRemainder(bs.buses, bs.remainders);

	std::cout << answer << std::endl;

	for (size_t index = 0; index < bs.buses.size(); ++index)
	{
		std::cout << "answer % bus = remainder "
			<< answer << " % " << bs.buses[index] << " = " << bs.remainders[index]
			<< " = " << answer % bs.buses[index]
			<< std::endl;
	}

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}

