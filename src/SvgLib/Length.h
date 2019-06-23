#pragma once
#include "Coordinate.h"

class Length : public Coordinate
{
public:
	Length(): Length(0)
	{
	}

	Length(double value)
		: Coordinate(value)
	{
	}

	Length(double value, UnitType unit)
		: Coordinate(value, unit)
	{
	}

	Length operator *(Length other) const
	{
		const double product_pixels = this->to_pixels() * other.to_pixels();
		const Length result(product_pixels);

		return result;
	}
};

inline Length pow(Length length, int power)
{
	if (power == 0)
	{
		return Length(1);
	}

	const Length half_power = pow(length, power / 2);
	Length result = half_power * half_power;
	if (power % 2 != 0)
	{
		result = result * length;
	}

	return result;
}
