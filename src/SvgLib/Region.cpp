#include "Region.h"

Region::Region(Coordinate x, Coordinate y)
{
	this->x = x;
	this->y = y;
}

bool Region::contains(const Shape& shape) const
{
	for (const Point& point : shape.boundary())
	{
		if (!this->contains(point))
			return false;
	}

	return true;
}

Region::~Region() = default;
