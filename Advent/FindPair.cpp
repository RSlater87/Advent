
#include <vector>
#include <map>

#include "FindPair.h"

int FindPair(std::vector<int>& nums, int target)
{
    std::map<int, int> products;

    for(auto& a : nums)
    {
        int product = (target - a) * a;
        if(products.find(product) != products.end())
        {
            //Found the pairing, return the multiple
            return product;
        }

        products[product] = a;
    }

    return 0;
}

int FindTriple(std::vector<int>& nums, int target)
{
    for(auto& a : nums)
    {
        int target2 = target - a;
        int product2 = FindPair(nums, target2);

        if(product2 == 0)
        {
            continue;
        }

        return product2 * a;
    }

    return 0;
}