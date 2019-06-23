#pragma once
#include "Region.h"
#include "Rectangle.h"
#include "Point.h"
#include "Length.h"

class CircleRegion : public Region
{
private:
	Length radius;

public:
	CircleRegion(const Coordinate& center_x, const Coordinate& center_y, const Length& radius);

	bool contains(const Point& point) const override;
};
