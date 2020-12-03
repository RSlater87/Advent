
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include "FindPair.h"
#include "ValidatePasswords.h"
#include "Utilities.h"
#include "RollingBuffer.h"
#include "CheckMap.h"

int main()
{
    std::vector<RollingBuffer<char>> inputs;
    std::fstream fs;
    fs.open ("day3.txt");

    while(fs.good())
    {
        char line[256];
        fs.getline(line, 256);
        std::string a(line);

        std::vector<char> row;
        std::copy(std::begin(a), std::end(a),
              std::back_inserter(row));

        inputs.push_back(RollingBuffer<char>(row));
    }

//Part 1
    {
        auto start = std::chrono::system_clock::now();
        std::cout << CountTrees(inputs, 3, 1) << std::endl;
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }

//Part 2
    {
        auto start = std::chrono::system_clock::now();
        size_t a = CountTrees(inputs, 1, 1);
        size_t b = CountTrees(inputs, 3, 1);
        size_t c = CountTrees(inputs, 5, 1);
        size_t d = CountTrees(inputs, 7, 1);
        size_t e = CountTrees(inputs, 1, 2);

        std::cout << a * b * c * d * e << std::endl;
        auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> diff = end-start;
        std::cout << "Time t: " << diff.count() << " s\n";
    }
    
    return 0;
}