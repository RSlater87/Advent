#pragma once

#include "export.h"

typedef long long PositionType;

struct DLLEXPORT Point
{
	PositionType x;
	PositionType y;
};

inline bool operator ==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator <(const Point& lhs, const Point& rhs)
{
	return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

struct DLLEXPORT Line
{
	Point a;
	Point b;
};

inline bool operator <(const Line& lhs, const Line& rhs)
{
	return (lhs.a < rhs.a) || ((lhs.a == rhs.a) && (lhs.b < rhs.b));
}

PositionType DLLEXPORT ManhattenDistance(Point a, Point b);