#include "BoardingPass.h"
#include "Customs.h"
#include "Luggage.h"

int main()
{
    auto inputs = Day7::ParseFile("Inputs/Day7.txt");
    Day7::Part1(inputs);
    Day7::Part2(inputs);
    
    return 0;
}