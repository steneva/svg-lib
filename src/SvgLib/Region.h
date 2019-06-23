#pragma once
#include "Coordinate.h"
#include "Shape.h"

class Region
{
protected:
	Coordinate x;
	Coordinate y;

public:
	Region(Coordinate x, Coordinate y);

	bool contains(const Shape& shape) const;

	virtual bool contains(const Point& point) const = 0;

	virtual ~Region();
};
