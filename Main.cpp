#include "BoardingPass.h"
#include "Customs.h"

int main()
{
    auto inputs = Day6::ParseFile("Inputs/Day6.txt");
    Day6::Part1(inputs);
    Day6::Part2(inputs);
    
    return 0;
}