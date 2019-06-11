#pragma once
#include "Length.h"

struct Point
{
	Length x;
	Length y;

	Point(const Length& x, const Length& y)
	{
		this->x = x;
		this->y = y;
	}
};
