#include "Utilities.h"

#include <sstream>
#include <algorithm>
#include <iterator>

std::vector<std::string> SplitString(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;

    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bool TryParseHexToNumber(const std::string& s, int& output)
{
    try
    {
        unsigned int x;   
        std::stringstream ss;
        ss << std::hex << s;
        ss >> x;

        output = static_cast<int>(x);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
}
