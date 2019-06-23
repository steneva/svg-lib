#include "Point.h"
Point::Point() = default;

Point::Point(const Coordinate& x, const Coordinate& y): Vector(x, y)
{
}

Point Point::operator+(const Vector& other) const
{
	return Point(x + other.x, y + other.y);
}
