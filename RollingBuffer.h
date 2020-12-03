#pragma once

#include <vector>

template<typename T>
class RollingBuffer
{
public:
    RollingBuffer(std::vector<T> v)
        : m_v(v),
            m_rows(v.size())
    {
    }

    T Get(size_t index) const 
    {
        return m_v[index % m_rows];
    }

private:
    size_t m_rows;
    std::vector<T> m_v;
};