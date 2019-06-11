#pragma once
#include "Region.h"
#include "Length.h"

struct RectangleRegion : public Region, public Boxable
{
private:
	Length width;
	Length height;
public:
	RectangleRegion(Length x, Length y, Length width, Length height)
		: Region(x, y)
	{
		this->width = width;
		this->height = height;
	}

	bool contains(const Shape& shape) override
	{
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
		return std::min(x, x + width);
	}

	Length rightmost() const override
	{
		return std::max(x, x + width);
	}

	Length topmost() const override
	{
		return std::min(x, x + height);
	}

	Length downmost() const override
	{
		return std::max(x, x + height);
	}
};
