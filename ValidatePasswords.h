#include <string>
#include <vector>

struct Password
{
    char rule;
    size_t lower;
    size_t upper;
    std::string password;
};

int ValidatePasswords_Part1(const std::vector<Password>& passwords);
bool IsPasswordValid_Part1(Password pwd);

int ValidatePasswords_Part2(const std::vector<Password>& passwords);
bool IsPasswordValid_Part2(Password pwd);