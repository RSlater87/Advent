#pragma once

#include "export.h"

struct DLLEXPORT Point
{
	int x;
	int y;
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

struct DLLEXPORT Vertex
{
	Point left;
	Point right;
};

inline bool operator <(const Vertex& lhs, const Vertex& rhs)
{
	return (lhs.left < rhs.left) || ((lhs.left == rhs.left) && (lhs.right < rhs.right));
}