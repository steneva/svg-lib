#pragma once
#include "Coordinate.h"
#include "Shape.h"

class Region
{
protected:
	Coordinate x;
	Coordinate y;

public:
	Region(Coordinate x, Coordinate y)
	{
		this->x = x;
		this->y = y;
	}

	bool contains(const Shape& shape) const
	{
		for (const Point& point : shape.boundary())
		{
			if (!this->contains(point))
				return false;
		}

		return true;
	}

	virtual bool contains(const Point& point) const = 0;

	virtual ~Region() = default;
};
