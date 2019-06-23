#include "PropertyValue.h"

void PropertyValue::parse(const std::string& value)
{
	try
	{
		parse_impl(value);
	}
	catch (std::invalid_argument&)
	{
		throw PropertyParseException(value);
	}
}

std::string PropertyValue::to_string() const
{
	std::ostringstream out;
	to_string_impl(out);
	return out.str();
}

std::ostream& operator<<(std::ostream& out, const PropertyValue& value)
{
	out << value.to_string();
	return out;
}
