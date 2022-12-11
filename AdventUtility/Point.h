#pragma once

#include "export.h"

struct DLLEXPORT Point
{
	int x;
	int y;
};

inline bool operator <(const Point& lhs, const Point& rhs)
{
	return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));;
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}