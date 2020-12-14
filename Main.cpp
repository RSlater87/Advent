#include "BoardingPass.h"
#include "Customs.h"
#include "Luggage.h"
#include "GameConsole.h"
#include "Xmas.h"
#include "Cables.h"
#include "Ferry.h"
#include "Manhatten.h"
#include "BusSchedule.h"
#include "Utilities.h"
#include <iostream>

int main()
{
    auto inputs = Day13::ParseFile("Inputs/Day13.txt");
    Day13::Part1(inputs);
    Day13::Part2(inputs);

    inputs = Day13::ParseFile("Inputs/test.txt");
    Day13::Part1(inputs);
    Day13::Part2(inputs);

    int num[] = { 3, 4, 5 };
    int rem[] = { 2, 3, 1 };

    std::cout << MinimumCommonRemainder({ 3, 5, 7 }, { 2, 3, 2 });
    
    return 0;
}