#pragma once
#include "PropertyValue.h"
#include <stdexcept>
#include <iomanip>

class Length;

class Coordinate : public PropertyValue
{
public:
	enum class UnitType
	{
		DEFAULT,
		PX,
	};

private:
	double _value = 0;
	UnitType _unit;

	static UnitType string_to_unit(const std::string& unit_str);

	static std::string unit_to_string(UnitType unit);

protected:

	double to_pixels() const;

	void parse_impl(const std::string& value) override;

public:

	Coordinate();

	Coordinate(double value);

	Coordinate(double value, UnitType unit);

	UnitType unit() const;

	double value() const;

	void to_string_impl(std::ostream& out) const override;

	bool operator <(Coordinate other) const;

	bool operator >=(Coordinate other) const;

	bool operator <=(Coordinate other) const;

	bool operator >(Coordinate other) const;

	bool operator ==(Coordinate other) const;

	Coordinate operator +(Coordinate other) const;

	Coordinate operator +(Length other) const;

	Coordinate& operator +=(const Coordinate& other);

	Coordinate& operator -=(const Coordinate& other);

	Length operator -(Coordinate other) const;

	Coordinate operator -(Length other) const;

	Coordinate operator *(Coordinate other) const;

	Coordinate operator /(const double& other) const;

	Coordinate& operator /=(const double& other);
};

inline Coordinate pow(Coordinate coordinate, int power)
{
	if (power == 0)
	{
		return Coordinate(1);
	}

	const Coordinate half_power = pow(coordinate, power / 2);
	Coordinate result = half_power * half_power;
	if (power % 2 != 0)
	{
		result = result * coordinate;
	}

	return result;
}
