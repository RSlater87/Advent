#include <vector>
#include <string>

template <typename A, typename B, typename C>
bool InRange(A a, B b, C c)
{
    return a >= std::min(b, c) && a <= std::max(b, c); 
}

std::vector<std::string> SplitString(const std::string& s, char delimiter);