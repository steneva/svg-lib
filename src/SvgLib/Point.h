#pragma once
#include "Vector.h"

struct Point: public Vector
{
public:
	Point() = default;

	Point(const Coordinate& x, const Coordinate& y)
		: Vector(x, y)
	{
	}

	Point operator+(const Vector& other) const
	{
		return Point(x + other.x, y + other.y);
	}
};
