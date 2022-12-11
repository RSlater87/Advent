#include <vector>
#include <string>
#include <algorithm>

#include "export.h"

template <typename A, typename B, typename C>
bool InRange(A a, B b, C c)
{
    return a >= std::min(b, c) && a <= std::max(b, c); 
}

std::string DLLEXPORT ReadAllText(const std::string& filename);
std::vector<std::string> DLLEXPORT SplitString(const std::string& s, char delimiter);
std::vector<std::string> DLLEXPORT SplitString(const std::string& str, const std::string& delimiter = " ");
std::string DLLEXPORT TrimLeft(const std::string& s);
std::string DLLEXPORT TrimRight(const std::string& s);
std::string DLLEXPORT Trim(const std::string& s);
std::string DLLEXPORT RemoveFirst(const std::string& s, const std::string& toRemove);

bool DLLEXPORT TryParseHexToNumber(const std::string& s, int& output);

int DLLEXPORT BinarySpacePartition(const std::vector<bool>& flags);

int64_t DLLEXPORT ModularMultiplicativeInverse(int64_t a, int64_t m);
int64_t DLLEXPORT MinimumCommonRemainder(const std::vector<int64_t>& numbers, const std::vector<int64_t>& remainders);