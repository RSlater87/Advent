#include "CheckMap.h"

int CountTrees(const std::vector<RollingBuffer<char>>& map, size_t right, size_t down)
{
    int count = 0;
    int column = right;
    for(size_t row = down; row < map.size(); row += down)
    {
        char loc = map[row].Get(column);
        if(loc == '#')
        {
            //Tree
            count++;
        }
        column += right;
    }   

    return count;
}