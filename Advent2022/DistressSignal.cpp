#include "DistressSignal.h"
#include "../AdventUtility/Utilities.h"
#include "../AdventUtility/Timer.h"
#include <iostream>

namespace
{
    const char StartList = '[';
    const char EndList = ']';
    const std::string EndListStr = "]";
    const std::string EndListWithComma = "],";

    const std::string Divider1 = "[[2]]";
    const std::string Divider2 = "[[6]]";
}

void DistressSignal::Part1(const std::string& filename)
{
    Timer t;

    auto allLines = SplitString(ReadAllText(filename), "\n");

    size_t count = 0;

    for (size_t index = 0; index < allLines.size(); index += 3)
    {
        std::string lhs = allLines[index];
        std::string rhs = allLines[index + 1];

        if (ArePacketsInOrder(lhs, rhs) == State::InOrder)
        {
            count += (index / 3) + 1;
        }
    }

    std::cout << count << std::endl;
}

void DistressSignal::Part2(const std::string& filename)
{
    Timer t;

    auto allLines = SplitString(ReadAllText(filename), "\n");

    //Get rid of empty lines
    std::vector<std::string> allPackets;
    std::copy_if(allLines.cbegin(), allLines.cend(), std::back_inserter(allPackets), [&](auto s) { return !s.empty(); });

    //Insert Divider Packets
    allPackets.push_back(Divider1);
    allPackets.push_back(Divider2);

    std::sort(allPackets.begin(), allPackets.end(), [&](const std::string& lhs, const std::string& rhs)
        {
            State state = ArePacketsInOrder(lhs, rhs);
            return state == State::InOrder;
        });

    auto index1 = std::distance(allPackets.begin(), std::find(allPackets.begin(), allPackets.end(), Divider1)) + 1;
    auto index2 = std::distance(allPackets.begin(), std::find(allPackets.begin(), allPackets.end(), Divider2)) + 1;
    auto decoderKey = index1 * index2;

    std::cout << decoderKey << std::endl;
}

DistressSignal::State DistressSignal::ArePacketsInOrder(std::string lhs, std::string rhs)
{
    auto lhsIter = lhs.cbegin();
    auto rhsIter = rhs.cbegin();

    State state = State::ContinueParsing;
    while (lhsIter != lhs.cend() && rhsIter != rhs.cend())
    {
        std::string subLeft, subRight;
        if (*lhsIter == StartList && *rhsIter == StartList)
        {
            //Compare two sub-lists
            lhsIter = FindAndExtractSubList(lhsIter, lhs.cend(), subLeft);
            rhsIter = FindAndExtractSubList(rhsIter, rhs.cend(), subRight);

            state = ArePacketsInOrder(subLeft, subRight);

            if (state != State::ContinueParsing)
            {
                return state;
            }

            //Otherwise move to next entry in sub-list
        }
        else if (std::isalnum(*lhsIter) && std::isalnum(*rhsIter))
        {
            //Compare two numbers
            lhsIter = FindAndExtractNumber(lhsIter, lhs.cend(), subLeft);
            rhsIter = FindAndExtractNumber(rhsIter, rhs.cend(), subRight);

            if (std::stoi(subLeft) < std::stoi(subRight))
            {
                return State::InOrder;
            }
            else if(std::stoi(subLeft) > std::stoi(subRight))
            {
                return State::OutOfOrder;
            }

            //Otherwise continue parsing
        }
        else if(std::isalnum(*lhsIter))
        {
            //Mixed types - elevate left to a list and then compare
            lhsIter = FindAndExtractNumber(lhsIter, lhs.cend(), subLeft);
            rhsIter = FindAndExtractSubList(rhsIter, rhs.cend(), subRight);

            state = ArePacketsInOrder(subLeft, subRight);

            if (state != State::ContinueParsing)
            {
                return state;
            }
        }
        else if (std::isalnum(*rhsIter))
        {
            //Mixed types - elevate right to a list and then compare
            lhsIter = FindAndExtractSubList(lhsIter, lhs.cend(), subLeft);
            rhsIter = FindAndExtractNumber(rhsIter, rhs.cend(), subRight);

            state = ArePacketsInOrder(subLeft, subRight);

            if (state != State::ContinueParsing)
            {
                return state;
            }
        }
    }

    //Check if lists are unbalanced
    if (lhsIter == lhs.cend() && rhsIter == rhs.cend())
    {
        //Lists agree so continue parsing
        return State::ContinueParsing;
    }
    if (lhsIter == lhs.cend())
    {
        return State::InOrder;
    }
    else // if (rhsIter == rhs.cend())
    {
        return State::OutOfOrder;
    }
}

std::string::const_iterator DistressSignal::FindSubList(std::string::const_iterator start, std::string::const_iterator end)
{
    auto current = start;
    int nests = 0;
    while (current != end)
    {
        if (*current == ']')
        {
            if (nests == 0)
            {
                break;
            }
            nests--;
        }

        if (*current == '[')
        {
            nests++;
        }

        current++;
    }

    return current;
}

std::string::const_iterator DistressSignal::FindAndExtractSubList(std::string::const_iterator start, std::string::const_iterator end, std::string& substr)
{
    auto found = FindSubList(start + 1, end);
    std::copy(start + 1, found, std::back_inserter(substr));

    if (found == end)
    {
        return end;
    }
    else if ((found + 1) == end) //Skip past commas as well
    {
        return found + 1;
    }
    else
    {
        return found + 2;
    }
}

std::string::const_iterator DistressSignal::FindAndExtractNumber(std::string::const_iterator start, std::string::const_iterator end, std::string& substr)
{
    auto found = std::find(start, end, ',');
    std::copy(start, found, std::back_inserter(substr));
    return (found == end) ? found : found + 1;
}
