#include "Boundary.h"

Boundary::Boundary(const std::vector<Point>& points)
{
	this->points = points;
}

Boundary::const_iterator Boundary::begin() const
{
	return points.begin();
}

Boundary::const_iterator Boundary::end() const
{
	return points.end();
}
