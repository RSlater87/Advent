#include "BoardingPass.h"
#include "Customs.h"
#include "Luggage.h"
#include "GameConsole.h"
#include "Xmas.h"
#include "Cables.h"
#include "Ferry.h"
#include "Manhatten.h"
#include "BusSchedule.h"
#include "Mask.h"
#include "Utilities.h"
#include <iostream>

int main()
{
    auto inputs = Day14::ParseFile("Inputs/Day14.txt");
    Day14::Part1(inputs);
    Day14::Part2(inputs);
    
    return 0;
}