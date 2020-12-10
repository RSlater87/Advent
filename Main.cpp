#include "BoardingPass.h"
#include "Customs.h"
#include "Luggage.h"
#include "GameConsole.h"
#include "Xmas.h"
#include "Cables.h"

int main()
{
    auto inputs = Day10::ParseFile("Inputs/Day10.txt");
    Day10::Part1(inputs);
    Day10::Part2(inputs);
    
    return 0;
}