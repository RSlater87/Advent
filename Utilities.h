#include <vector>
#include <string>

template <typename A, typename B, typename C>
bool InRange(A a, B b, C c)
{
    return a >= std::min(b, c) && a <= std::max(b, c); 
}

std::string ReadAllText(const std::string& filename);
std::vector<std::string> SplitString(const std::string& s, char delimiter);
std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter = " ");

bool TryParseHexToNumber(const std::string& s, int& output);

int BinarySpacePartition(const std::vector<bool>& flags);