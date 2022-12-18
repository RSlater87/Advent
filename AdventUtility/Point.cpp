#include "pch.h"

#include "Point.h"
#include <cmath>

PositionType ManhattenDistance(Point a, Point b)
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}
