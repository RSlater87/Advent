#include "BoardingPass.h"
#include "Customs.h"
#include "Luggage.h"
#include "GameConsole.h"
#include "Xmas.h"

int main()
{
    auto inputs = Day9::ParseFile("Inputs/Day9.txt");
    int invalidNumber = Day9::Part1(inputs);
    Day9::Part2(inputs, invalidNumber);
    
    return 0;
}