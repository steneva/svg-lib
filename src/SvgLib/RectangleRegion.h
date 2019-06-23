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
	RectangleRegion(Coordinate x, Coordinate y, Length width, Length height)
		: Region(x, y)
	{
		this->width = width;
		this->height = height;
	}

	bool contains(const Point& point) const override
	{
		const Coordinate min_x = std::min(x + width, x);
		const Coordinate min_y = std::min(y + height, y);
		const Coordinate max_x = std::max(x + width, x);
		const Coordinate max_y = std::max(y + height, y);

		return point.x >= min_x && point.x <= max_x
			&& point.y >= min_y && point.y <= max_y;
	}
};
