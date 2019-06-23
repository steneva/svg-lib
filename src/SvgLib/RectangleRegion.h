#pragma once
#include "Region.h"
#include "Coordinate.h"
#include "Length.h"

class RectangleRegion : public Region
{
private:
	Length width;
	Length height;
public:
	RectangleRegion(Coordinate x, Coordinate y, Length width, Length height);

	bool contains(const Point& point) const override;
};
