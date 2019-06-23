#include "Vector.h"
#include "Point.h"

Vector::Vector() = default;

Vector::Vector(const Coordinate& x, const Coordinate& y)
{
	this->x = x;
	this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Vector& point)
{
	return os << point.x << " " << point.y;
}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator+(const Point& other) const
{
	return Vector(x + other.x, y + other.y);
}
