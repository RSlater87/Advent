#include "Passport.h"
#include "../AdventUtility/Utilities.h"

Passport Parse(const std::string& s)
{
    Passport p;

    auto parts = SplitString(s, ' ');
    for(auto& part : parts)
    {
        auto kvp = SplitString(part, ':');
        if(kvp.size() < 2)
        {
            continue;
        }

        if(kvp[0] == "byr")
        {
            p.BirthYear = std::stoi(kvp[1]);
        }
        else if(kvp[0] == "iyr")
        {
            p.IssueYear = std::stoi(kvp[1]);
        }
        else if(kvp[0] == "eyr")
        {
            p.ExpYear = std::stoi(kvp[1]);
        }
        else if(kvp[0] == "hgt")
        {
            p.Height = kvp[1];
        }
        else if(kvp[0] == "hcl")
        {
            p.HairColour = kvp[1];
        }
        else if(kvp[0] == "ecl")
        {
            p.EyeColour = kvp[1];
        }
        else if(kvp[0] == "pid")
        {
            p.PassportID = kvp[1];
        }
        else if(kvp[0] == "cid")
        {
            p.CountryID = kvp[1];
        }

    }

    return p;
}

bool IsValid_Part1(const Passport& p)
{
    return p.BirthYear.has_value()
        //&& p.CountryID.has_value()
        && p.ExpYear.has_value()
        && p.EyeColour.has_value()
        && p.HairColour.has_value()
        && p.Height.has_value()
        && p.IssueYear.has_value()
        && p.PassportID.has_value();
}

bool IsValid_Part2(const Passport& p)
{
    return p.BirthYear.has_value() && InRange(p.BirthYear.value(), 1920, 2002)
        //&& p.CountryID.has_value()
        && p.ExpYear.has_value() && InRange(p.ExpYear.value(), 2020, 2030)
        && p.EyeColour.has_value() && IsEyeColourValid(p.EyeColour.value())
        && p.HairColour.has_value() && IsHairColourValid(p.HairColour.value())
        && p.Height.has_value() && IsHeightValid(p.Height.value())
        && p.IssueYear.has_value() && InRange(p.IssueYear.value(), 2010, 2020)
        && p.PassportID.has_value() && IsPassportIDValid(p.PassportID.value());
}

bool IsHeightValid(const std::string& hgt)
{
    if(hgt.size() <= 2)
    {
        return false;
    }

    std::string units = hgt.substr(hgt.size() - 2, 2);
    int value = std::stoi(hgt.substr(0, hgt.size() - 2));

    if(units == "cm")
    {
        return InRange(value, 150, 193);
    }
    else if(units == "in")
    {
        return InRange(value, 59, 76);
    }

    return false;
}

bool IsHairColourValid(const std::string& hcl)
{
    int dummy;

    return hcl[0] == '#'
    && TryParseHexToNumber(hcl.substr(1), dummy);
}

bool IsEyeColourValid(const std::string& ecl)
{
    return ecl == "amb"
    || ecl == "blu"
    || ecl == "brn"
    || ecl == "gry"
    || ecl == "grn"
    || ecl == "hzl"
    || ecl == "oth";
}

bool IsPassportIDValid(const std::string& pid)
{
    return pid.size() == 9;
}