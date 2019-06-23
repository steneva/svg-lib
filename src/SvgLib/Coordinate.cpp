#include "Coordinate.h"
#include "Length.h"
#include "PropertyParseException.h"

Coordinate::UnitType Coordinate::string_to_unit(const std::string& unit_str)
{
	if (unit_str == "px")
	{
		return UnitType::PX;
	}

	return UnitType::DEFAULT;
}

std::string Coordinate::unit_to_string(UnitType unit)
{
	switch (unit)
	{
		case UnitType::PX:
			return "";
		default:
			return "";
	}
}

double Coordinate::to_pixels() const
{
	switch (_unit)
	{
		case UnitType::DEFAULT:
		case UnitType::PX:
			return this->_value;
		default:
			throw std::runtime_error("Unit not supported.");
	}
}

Coordinate::Coordinate(): Coordinate(0)
{
}

Coordinate::Coordinate(double value): Coordinate(value, UnitType::DEFAULT)
{
}

Coordinate::Coordinate(double value, UnitType unit)
{
	this->_value = value;
	this->_unit = unit;
}

Coordinate::UnitType Coordinate::unit() const
{
	return _unit;
}

double Coordinate::value() const
{
	return _value;
}

void Coordinate::to_string_impl(std::ostream& out) const
{
	out << _value;
	if (_unit != UnitType::DEFAULT)
	{
		out << unit_to_string(this->_unit);
	}
}

void Coordinate::parse_impl(const std::string& value)
{
	const std::string::size_type last_digit_index = value.find_last_of("0123456789");

	const std::string value_str = value.substr(0, last_digit_index + 1);
	const std::string unit_str = value.substr(last_digit_index + 1);

	this->_value = stod(value_str);
	this->_unit = string_to_unit(unit_str);
}

bool Coordinate::operator<(Coordinate other) const
{
	return this->to_pixels() < other.to_pixels();
}

bool Coordinate::operator>=(Coordinate other) const
{
	return this->to_pixels() >= other.to_pixels();
}

bool Coordinate::operator<=(Coordinate other) const
{
	return this->to_pixels() <= other.to_pixels();
}

bool Coordinate::operator>(Coordinate other) const
{
	return this->to_pixels() > other.to_pixels();
}

bool Coordinate::operator==(Coordinate other) const
{
	return this->to_pixels() == other.to_pixels();
}

Coordinate Coordinate::operator+(Coordinate other) const
{
	const double sum_pixels = this->to_pixels() + other.to_pixels();
	const Coordinate result(sum_pixels, UnitType::PX);

	return result;
}

Coordinate Coordinate::operator+(Length other) const
{
	const double sum_pixels = this->to_pixels() + other.to_pixels();
	const Coordinate result(sum_pixels, UnitType::PX);

	return result;
}

Coordinate& Coordinate::operator+=(const Coordinate& other)
{
	return *this = *this + other;
}

Coordinate& Coordinate::operator-=(const Coordinate& other)
{
	return *this = *this - other;
}

Length Coordinate::operator-(Coordinate other) const
{
	const double diff_pixels = this->to_pixels() - other.to_pixels();
	const Length result(diff_pixels, UnitType::PX);

	return result;
}

Coordinate Coordinate::operator-(Length other) const
{
	const double diff_pixels = this->to_pixels() - other.to_pixels();
	const Coordinate result(diff_pixels, UnitType::PX);

	return result;
}

Coordinate Coordinate::operator*(Coordinate other) const
{
	const double product_pixels = this->to_pixels() * other.to_pixels();
	Coordinate result(product_pixels, UnitType::PX);

	return result;
}

Coordinate Coordinate::operator/(const double& other) const
{
	return Coordinate(this->_value / other, this->_unit);
}

Coordinate& Coordinate::operator/=(const double& other)
{
	*this = *this / other;
	return *this;
}
