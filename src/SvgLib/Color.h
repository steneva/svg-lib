#pragma once
#include "PropertyValue.h"

class Color : public PropertyValue
{
private:
	std::string value;

protected:
	void parse_impl(const std::string& value) override
	{
		this->value = value;
	}

public:
	Color() : value("black")
	{
	}

	Color(const std::string& color)
	{
		this->value = color;
	}

	void to_string_impl(std::ostream& out) const override
	{
		out << value;
	}
};
