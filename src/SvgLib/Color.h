#pragma once
#include "PropertyValue.h"

class Color : public PropertyValue
{
private:
	std::string value;

protected:
	void parse_impl(const std::string& value) override;

public:
	Color();

	Color(const std::string& color);

	void to_string_impl(std::ostream& out) const override;
};
