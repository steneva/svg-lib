#include "Length.h"

Length::Length(): Length(0)
{
}

Length::Length(double value): Coordinate(value)
{
}

Length::Length(double value, UnitType unit): Coordinate(value, unit)
{
}

Length Length::operator*(Length other) const
{
	const double product_pixels = this->to_pixels() * other.to_pixels();
	const Length result(product_pixels);

	return result;
}
