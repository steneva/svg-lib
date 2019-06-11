#pragma once
#include "PropertyValue.h"

class Color : public PropertyValue
{
	std::string value;

public:
	Color() :value("black") {  }

	Color(const std::string& color)
	{
		this->value = color;
	}

	void parse(const std::string& value) override
	{
		this->value = value;
	}

	void to_string_impl(std::ostream& out) const override
	{
		out << value;
	}
};
