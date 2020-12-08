#include "BoardingPass.h"
#include "Customs.h"
#include "Luggage.h"
#include "GameConsole.h"

int main()
{
    auto inputs = Day8::ParseFile("Inputs/Day8.txt");
    Day8::Part1(inputs);
    Day8::Part2(inputs);
    
    return 0;
}