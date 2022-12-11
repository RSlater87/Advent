// Advent2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "RopeTracking.h"
#include "CathodeRayTube.h"
#include "MonkeyBusiness.h"
 
int main()
{
    MonkeyBusiness::PerformOperations("Inputs/2022-11.txt", 20, 3, 8);

    MonkeyBusiness::PerformOperations("Inputs/2022-11.txt", 10000, 1, 8);

    return 0;
}