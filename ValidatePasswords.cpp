#include "ValidatePasswords.h"
#include "Utilities.h"

#include <algorithm>

int ValidatePasswords_Part1(const std::vector<Password>& passwords)
{
    return std::count_if(passwords.cbegin(), passwords.cend(), IsPasswordValid_Part1);
}

bool IsPasswordValid_Part1(Password pwd)
{
    return InRange(std::count(pwd.password.cbegin(), pwd.password.cend(), pwd.rule), pwd.lower, pwd.upper);
}

int ValidatePasswords_Part2(const std::vector<Password>& passwords)
{
    return std::count_if(passwords.cbegin(), passwords.cend(), IsPasswordValid_Part2);
}

bool IsPasswordValid_Part2(Password pwd)
{
    bool left = pwd.password[pwd.lower - 1] != pwd.rule;
    bool right = pwd.password[pwd.upper - 1] != pwd.rule;

    bool test = left != right;

    return test; //XOR comparison
}