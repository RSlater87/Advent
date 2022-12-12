// Advent2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "RopeTracking.h"
#include "CathodeRayTube.h"
#include "MonkeyBusiness.h"
#include "HillClimbingAlgorithm.h"
 
int main()
{
    auto heatmap = HillClimbingAlgorithm::ParseFile("Inputs/2022-12.txt");

    HillClimbingAlgorithm::Part1(heatmap);
    HillClimbingAlgorithm::Part2(heatmap);

    return 0;
}