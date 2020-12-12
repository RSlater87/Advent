#include "BoardingPass.h"
#include "Customs.h"
#include "Luggage.h"
#include "GameConsole.h"
#include "Xmas.h"
#include "Cables.h"
#include "Ferry.h"
#include "Manhatten.h"

int main()
{
    auto inputs = Day12::ParseFile("Inputs/Day12.txt");
    Day12::Part1(inputs);
    Day12::Part2(inputs);
    
    return 0;
}