// Advent2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
 
#include "BeaconDetection.h"
#include "../AdventUtility/Point.h"
#include <iostream>

int main()
{
    auto sensorDetails = BeaconDetection::ParseFile("Inputs/2022-15.txt");

    BeaconDetection::Part1(sensorDetails, 2000000);
    BeaconDetection::Part2(sensorDetails, 4000000);

    return 0;
}