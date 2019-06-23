#pragma once
#include "Coordinate.h"

struct Point;

struct Vector
{
public:
	Coordinate x;
	Coordinate y;

	Vector();

	Vector(const Coordinate& x, const Coordinate& y);

	friend std::ostream& operator<<(std::ostream& os, const Vector& point);

	Vector operator+(const Vector& other) const;

	Vector operator+(const Point& other) const;
};
