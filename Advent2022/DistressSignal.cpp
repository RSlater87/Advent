#include "DistressSignal.h"
#include "../AdventUtility/Utilities.h"

int DistressSignal::Part1_ParseAndCompare(const std::string& filename)
{
    auto allLines = SplitString(ReadAllText(filename), "\n");

    int count = 0;

    for (size_t index = 0; index < allLines.size(); index += 3)
    {
        std::string lhs = allLines[index];
        std::string rhs = allLines[index + 1];

        if (ArePacketsInOrder(lhs, rhs))
        {
            count++;
        }
    }

    return 0;
}

bool DistressSignal::ArePacketsInOrder(const std::string& lhs, const std::string& rhs)
{
    if (lhs.empty())
    {
        //if left is empty, assume right is in order
        return true;
    }

    if (rhs.empty())
    {
        //right is empty, then right is out of order
        return false;
    }

    if (lhs[0] == '[' && rhs[0] == '[')
    {
        //Comparing two lists, extract the lists and compare each value
        std::string leftList = lhs.substr(1, lhs.size() - 2);
        std::string rightList = rhs.substr(1, lhs.size() - 2);

        return ArePacketsInOrder(leftList, rightList);
    }
    else
    {
        //break up the lists and compare in turn 
        auto partsLeft = SplitString(lhs, ",");
        auto partsRight = SplitString(rhs, ",");
        bool isInOrder = true;
        for (size_t index = 0; index < partsLeft.size() && index < partsRight.size(); ++index)
        {
            if (partsLeft[index][0] == '[' && partsRight[index][0] == '[')
            {
                //Compare the two sub-lists
                isInOrder = isInOrder || ArePacketsInOrder(partsLeft[index], partsRight[index]);
            }
            else if (partsLeft[index][0] == '[')    //Right is not a list
            {
                //Compare two sub-lists, as if right is a list
                isInOrder = isInOrder || ArePacketsInOrder(partsLeft[index], "[" + partsRight[index] + "]");
            }
            else if (partsRight[index][0] == '[') //Left is not a list
            {
                //Compare two sub-lists, as if left is a list
                isInOrder = isInOrder || ArePacketsInOrder("[" + partsLeft[index] + "]", partsRight[index]);
            }
            else
            {
                //Compare two numbers
                if (std::stoi(partsLeft[index]) < std::stoi(partsRight[index]))
                {
                    isInOrder = true;
                    break;
                }
                else if (std::stoi(partsLeft[index]) > std::stoi(partsRight[index]))
                {
                    isInOrder = false;
                    break;
                }
            }
        }
    }
   
    return false;
}
