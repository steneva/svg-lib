#pragma once
#include "Region.h"
#include "Rectangle.h"
#include "Point.h"
#include "Circle.h"

class CircleRegion : public Region, public Boxable
{
private:
	Length radius;

	bool contains(Point point) const
	{
		const Length diff_x_squared = pow(x - point.x, 2);
		const Length diff_y_squared = pow(y - point.y, 2);

		return diff_x_squared <= radius && diff_y_squared <= radius;
	}

public:

	bool contains(const Shape& shape) override
	{
		if (const auto rectangle = dynamic_cast<const Rectangle*>(&shape))
		{
			Point top_left_corner(rectangle->leftmost(), rectangle->topmost());
			Point top_right_corner(rectangle->rightmost(), rectangle->topmost());
			Point bottom_left_corner(rectangle->leftmost(), rectangle->downmost());
			Point bottom_right_corner(rectangle->rightmost(), rectangle->downmost());

			return contains(top_left_corner)
				&& contains(top_right_corner)
				&& contains(bottom_left_corner)
				&& contains(bottom_right_corner);
		}
		else if (const auto circle = dynamic_cast<const Circle*>(&shape))
		{
		}

		const bool contains_x =
			this->leftmost() <= shape.leftmost()
			&& this->rightmost() >= shape.rightmost();

		const bool contains_y =
			this->topmost() <= shape.topmost()
			&& this->downmost() >= shape.downmost();

		return contains_x && contains_y;
	}

	Length leftmost() const override
	{
		// TODO: implement
		return Length(0);
	}

	Length rightmost() const override
	{
		// TODO: implement
		return Length(0);
	}

	Length topmost() const override
	{
		// TODO: implement
		return Length(0);
	}

	Length downmost() const override
	{
		// TODO: implement
		return Length(0);
	}
};
