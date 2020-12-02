
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "FindPair.h"
#include "ValidatePasswords.h"
#include "Utilities.h"

int main()
{
    std::vector<Password> inputs;
    std::fstream fs;
    fs.open ("day2.txt");

    while(fs.good())
    {
        char line[256];
        fs.getline(line, 256);

        auto parts = SplitString(line, ' ');
        auto limits = SplitString(parts[0], '-');

        Password pwd;
        pwd.lower = std::stoi(limits[0]);
        pwd.upper = std::stoi(limits[1]);
        pwd.rule = parts[1][0];
        pwd.password = parts[2];

        inputs.push_back(pwd);
    }

//Part 1
    {
        auto start = std::chrono::system_clock::now();
        std::cout << ValidatePasswords_Part1(inputs) << std::endl;
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }

//Part 2
    {
        auto start = std::chrono::system_clock::now();
        std::cout << ValidatePasswords_Part2(inputs) << std::endl;
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }
    
    return 0;
}