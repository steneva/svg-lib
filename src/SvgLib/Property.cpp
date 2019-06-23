#include "Property.h"

Coordinate Property::coordinate(const std::string& value)
{
	return create<Coordinate>(value, "coordinate");
}

Length Property::length(const std::string& value)
{
	return create<Length>(value, "length");
}

Color Property::color(const std::string& value)
{
	return create<Color>(value, "color");
}
