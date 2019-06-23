#include "CircleRegion.h"

CircleRegion::CircleRegion(const Coordinate& center_x, const Coordinate& center_y, const Length& radius): Region(
	center_x, center_y)
{
	this->radius = radius;
}

bool CircleRegion::contains(const Point& point) const
{
	const Length diff_x_squared = pow(x - point.x, 2);
	const Length diff_y_squared = pow(y - point.y, 2);

	const Length radius_squared = pow(radius, 2);

	return diff_x_squared <= radius_squared && diff_y_squared <= radius_squared;
}
