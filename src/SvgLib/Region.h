#pragma once
#include "Length.h"
#include "Shape.h"

class Region
{
protected:
	Length x;
	Length y;
public:
	Region(Length x, Length y)
	{
		this->x = x;
		this->y = y;
	}

	virtual bool contains(const Shape& shape) const = 0;

	virtual ~Region() = default;
};
