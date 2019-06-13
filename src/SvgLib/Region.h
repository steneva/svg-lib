﻿#pragma once
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
		x = x;
		y = y;
	}

	virtual bool contains(const Shape& shape) = 0;

	virtual ~Region() = default;
};