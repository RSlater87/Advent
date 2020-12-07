#include "Utilities.h"

#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

std::string ReadAllText(const std::string& filename)
{
    std::ifstream is{ filename, std::ios::binary | std::ios::ate };

    if (!is)
    {
        return ""; 
    }
    
    auto size = is.tellg();
    std::string str(size, '\0'); // construct string to stream size
    is.seekg(0);
    is.read(&str[0], size);

    return str;
}

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

std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter /*= " "*/)
{
    std::vector<std::string> cont;
    std::size_t current, previous = 0;
    current = str.find(delimiter);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + delimiter.size();
        current = str.find(delimiter, previous);
    }
    cont.push_back(str.substr(previous, current - previous));

    return cont;
}

std::string TrimLeft(const std::string& s)
{
    auto copy = s;
    copy.erase(copy.begin(), std::find_if(copy.begin(), copy.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));

    return copy;
}

std::string TrimRight(const std::string& s)
{
    auto copy = s;
    copy.erase(std::find_if(copy.rbegin(), copy.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), copy.end());

    return copy;
}

std::string Trim(const std::string& s)
{
    auto l = TrimLeft(s);
    auto r = TrimRight(l);

    return r;
}

std::string RemoveFirst(const std::string& s, const std::string& toRemove)
{
    auto found = s.find(toRemove);
    if (found != std::string::npos)
    {
        auto copy = s;
        copy.erase(std::begin(copy) + found, std::begin(copy) + found + toRemove.size());
        return copy;
    }

    return s;
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

int BinarySpacePartition(const std::vector<bool>& flags)
{
    int start = 0;
    int end = std::pow(2, flags.size()) - 1;

    int result = 0;
    for (const auto& f : flags)
    {
        int mid = (start + end) / 2;
        if (f)
        {
            end = mid;
            result = start;
        }
        else
        {
            start = mid + 1;
            result = end;
        }
    }

    return result;
}