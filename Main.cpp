
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

int main()
{
    std::vector<Passport> inputs;
    std::fstream fs;
    fs.open ("Inputs/day4.txt");

    std::string entry = "";
    while(fs.good())
    {
        char line[256];
        fs.getline(line, 256);
        std::string part(line);

        if(part.empty())
        {
            inputs.push_back(Parse(entry));
            entry = "";
        }
        else
        {
            entry += " ";
            entry += part;
        }
    }

//Part 1
    {
        auto start = std::chrono::system_clock::now();
        std::cout << std::count_if(inputs.cbegin(), inputs.cend(), IsValid_Part1) << std::endl;
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }

//Part 2
    {
        auto start = std::chrono::system_clock::now();
        std::cout << std::count_if(inputs.cbegin(), inputs.cend(), IsValid_Part2) << std::endl;
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }
    
    return 0;
}