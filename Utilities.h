#include <vector>
#include <string>
#include <algorithm>

template <typename A, typename B, typename C>
bool InRange(A a, B b, C c)
{
    return a >= std::min(b, c) && a <= std::max(b, c); 
}

std::string ReadAllText(const std::string& filename);
std::vector<std::string> SplitString(const std::string& s, char delimiter);
std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter = " ");
std::string TrimLeft(const std::string& s);
std::string TrimRight(const std::string& s);
std::string Trim(const std::string& s);
std::string RemoveFirst(const std::string& s, const std::string& toRemove);

bool TryParseHexToNumber(const std::string& s, int& output);

int BinarySpacePartition(const std::vector<bool>& flags);

int64_t ModularMultiplicativeInverse(int64_t a, int64_t m);
int64_t MinimumCommonRemainder(const std::vector<int64_t>& numbers, const std::vector<int64_t>& remainders);