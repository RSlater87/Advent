#include "Xmas.h"

#include "Utilities.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <algorithm>

std::vector<int> Day9::ParseFile(const std::string& file)
{
	std::ifstream fs{ file };
	std::vector<int> buffer;
	while (fs.good())
	{
		int number;
		fs >> number;
		buffer.push_back(number);
	}

	return buffer;
}

int Day9::Part1(const std::vector<int>& numbers)
{
	auto start = std::chrono::system_clock::now();

	size_t preamble = 25;
	std::list<int> buffer;
	std::list<int> validSumsSize;
	std::list<int> validSums;
	int count = 0;
	int invalidNumber = 0;

	for(auto& number: numbers)
	{
		count++;

		//Check number is valid by comparing to possible sums
		if (count > preamble)
		{
			auto found = std::find(validSums.begin(), validSums.end(), number);

			if (found == validSums.end())
			{
				invalidNumber = number;
				break;
			}
		}

		//add to possible sums
		size_t sumSize = 0;
		for (auto& prev : buffer)
		{
			if (prev != number)
			{
				validSums.push_back(prev + number);
				sumSize++;
			}
		}
		buffer.push_back(number);
		validSumsSize.push_back(sumSize);

		//remove the first number from the buffer
		if (count > preamble)
		{
			buffer.pop_front();
			size_t numSumsToRemove = validSumsSize.front();
			for (size_t index = 0; index < numSumsToRemove; ++index)
			{
				validSums.pop_front();
			}
			validSumsSize.pop_front();
		}
	}

	std::cout << invalidNumber << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";

	return invalidNumber;
}

void Day9::Part2(const std::vector<int>& numbers, int invalidNumber)
{
	auto start = std::chrono::system_clock::now();
	int answer = 0;

	//loop over each number and find the range that sums to the target
	for (auto a = numbers.cbegin(); a != numbers.cend(); ++a)
	{
		//loop over this range until sum is equals or greater than target
		int sum = 0;
		auto start = a, end = a;
		for (auto b = a; b != numbers.cend(); ++b)
		{
			sum += *b;
			end = b;

			if (sum >= invalidNumber)
			{
				break;
			}
		}

		if (sum == invalidNumber)
		{
			auto minmax = std::minmax_element(start, end);

			answer = *minmax.first + *minmax.second;
			break;
		}
	}

	std::cout << answer << std::endl;

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start;
	std::cout << "Time t: " << diff.count() << " s\n";
}