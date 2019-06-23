#pragma once
#include "Vector.h"

struct Point: public Vector
{
public:
	Point();

	Point(const Coordinate& x, const Coordinate& y);

	Point operator+(const Vector& other) const;
};
