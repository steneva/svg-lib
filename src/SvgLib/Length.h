#pragma once
#include "PropertyValue.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>

class Length : public PropertyValue
{
public:
	enum class UnitType
	{
		DEFAULT,
		PX,
	};

private:
	double value;

	static UnitType string_to_unit(const std::string& unit_str)
	{
		if (unit_str == "px")
		{
			return UnitType::PX;
		}

		return UnitType::DEFAULT;
	}

	static std::string unit_to_string(UnitType unit)
	{
		switch (unit)
		{
			case UnitType::PX:
				return "px";
			default:
				return "";
		}
	}

	double to_pixels() const
	{
		switch (unit)
		{
			case UnitType::DEFAULT:
			case UnitType::PX:
				return this->value;
			default:
				throw std::runtime_error("Unit not supported.");
		}
	}

public:

	Length()
		: value(0), unit(UnitType::DEFAULT)
	{
	}

	Length(double value)
		: Length(value, UnitType::DEFAULT)
	{
	}

	Length(double value, UnitType unit)
	{
		this->value = value;
		this->unit = unit;
	}

	UnitType unit;

	void to_string_impl(std::ostream& out) const override
	{
		out << value << unit_to_string(this->unit);
	}

	void parse(const std::string& value) override
	{
		const std::string::size_type last_digit_index = value.find_last_of("0123456789");

		const std::string value_str = value.substr(0, last_digit_index + 1);
		const std::string unit_str = value.substr(last_digit_index + 1);

		this->value = stoi(value_str);
		this->unit = string_to_unit(unit_str);
	}

	bool operator <(Length other) const
	{
		return this->to_pixels() < other.to_pixels();
	}

	bool operator >=(Length other) const
	{
		return this->to_pixels() >= other.to_pixels();
	}

	bool operator <=(Length other) const
	{
		return this->to_pixels() <= other.to_pixels();
	}

	bool operator >(Length other) const
	{
		return this->to_pixels() > other.to_pixels();
	}

	bool operator ==(Length other) const
	{
		return this->to_pixels() == other.to_pixels();
	}

	Length operator +(Length other) const
	{
		const double sum_pixels = this->to_pixels() + other.to_pixels();
		const Length result(sum_pixels, UnitType::PX);

		return result;
	}

	Length operator -(Length other) const
	{
		const double diff_pixels = this->to_pixels() - other.to_pixels();
		const Length result(diff_pixels, UnitType::PX);

		return result;
	}

	Length operator *(Length other) const
	{
		const double product_pixels = this->to_pixels() * other.to_pixels();
		const Length result(product_pixels, UnitType::PX);

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
