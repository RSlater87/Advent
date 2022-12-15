// Advent2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "RopeTracking.h"
#include "CathodeRayTube.h"
#include "MonkeyBusiness.h"
#include "HillClimbingAlgorithm.h"
#include "DistressSignal.h"
#include "SandSimulator.h"
 
int main()
{
    auto caveMap = SandSimulator::ParseFile("Inputs/2022-14.txt");

    SandSimulator::Part1(caveMap);
    SandSimulator::Part2(caveMap);

    return 0;
}