
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "FindPair.h"
#include "ValidatePasswords.h"
#include "Utilities.h"
#include "RollingBuffer.h"
#include "CheckMap.h"
#include "Passport.h"
#include "BoardingPass.h"

int main()
{
    std::vector<BoardingPass> inputs;
    std::fstream fs;
    fs.open ("Inputs/day5.txt");

    while(fs.good())
    {
        std::string line;
        std::getline(fs, line);
        if (!line.empty())
        {
            inputs.push_back(ParseBoardingPass(line));
        }
    }

//Part 1
    {
        auto start = std::chrono::system_clock::now();
        auto max = std::max_element(inputs.cbegin(), inputs.cend(), CompareSeatId);
        std::cout << (*max).SeatID << std::endl;
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }

//Part 2
    {
        auto start = std::chrono::system_clock::now();

        //Sort the boarding passes by Seat ID
        auto sortedInputs = inputs;
        std::sort(sortedInputs.begin(), sortedInputs.end(), CompareSeatId);

        //Find missing seat IDs using lower bound
        for (int i = 68; i < 965; ++i)
        {
            auto lower = std::lower_bound(sortedInputs.begin(), sortedInputs.end(), i, [&](const BoardingPass& p, int i)
                {
                    return p.SeatID < i;
                });

            if (lower != sortedInputs.cend() && lower->SeatID != i)
            {
                //Couldn't find i
                std::cout << "Missing: " << i << std::endl;
            }
        }
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }

    {
        auto start = std::chrono::system_clock::now();

        //Find missing seat IDs using lower bound
        for (int i = 68; i < 965; ++i)
        {
            auto lower = std::find_if(inputs.begin(), inputs.end(), [&](const BoardingPass& p)
                {
                    return p.SeatID == i;
                });

            if (lower == inputs.cend())
            {
                //Couldn't find i
                std::cout << "Missing: " << i << std::endl;
            }
        }
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end - start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }
    
    return 0;
}