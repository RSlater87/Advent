#include "pch.h"

#include "Utilities.h"


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
    if (!str.substr(previous, current - previous).empty())
    {
        cont.push_back(str.substr(previous, current - previous));
    }
   

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
    catch(const std::exception&)
    {
        return false;
    }
}

int BinarySpacePartition(const std::vector<bool>& flags)
{
    int start = 0;
    int end = static_cast<int>(std::pow(2, flags.size()) - 1);

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

int64_t ModularMultiplicativeInverse(int64_t a, int64_t m)
{
    int64_t m0 = m, t, q;
    int64_t x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    // Apply extended Euclid Algorithm 
    while (a > 1)
    {
        // q is quotient 
        q = a / m;

        t = m;

        // m is remainder now, process same as 
        // euclid's algo 
        m = a % m, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive 
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int64_t MinimumCommonRemainder(const std::vector<int64_t>& numbers, const std::vector<int64_t>& remainders)
{
    /*
    Use Chinese remainder theorum to solve this.
    We want to find x such that
    x % competition[0] = 0,
    x % competition[1] = 1,
        .......................
    x % competition[k - 1] = k - 1

    x =  ( ∑ (rem[i]*pp[i]*inv[i]) ) % prod
    Where 0 <= i <= n-1

    rem[i] is given array of remainders

    prod is product of all given numbers
    prod = num[0] * num[1] * ... * num[k-1]

    pp[i] is product of all divided by num[i]
    pp[i] = prod / num[i]

    inv[i] = Modular Multiplicative Inverse of
                pp[i] with respect to num[i]

    */

    size_t product = std::accumulate(numbers.cbegin(), numbers.cend(), size_t{ 1 }, [&](size_t total, size_t value)
        {
            return total * value;
        });

    size_t total = 0;
    for (size_t index = 0; index < numbers.size(); ++index)
    {
        size_t pp = product / numbers[index];
        size_t inv = ModularMultiplicativeInverse(pp, numbers[index]);

        total += (remainders[index] * pp * inv);
    }

    return total % product;
}
