#include <optional>
#include <string>

struct Passport
{
public:
    std::optional<int> BirthYear;
    std::optional<int> IssueYear;
    std::optional<int> ExpYear;
    std::optional<std::string> Height;
    std::optional<std::string> HairColour;
    std::optional<std::string> EyeColour;
    std::optional<std::string> PassportID;
    std::optional<std::string> CountryID;
};

Passport Parse(const std::string& s);

bool IsValid_Part1(const Passport& p);
bool IsValid_Part2(const Passport& p);

bool IsHeightValid(const std::string& hgt);
bool IsHairColourValid(const std::string& hcl);
bool IsEyeColourValid(const std::string& ecl);
bool IsPassportIDValid(const std::string& pid);