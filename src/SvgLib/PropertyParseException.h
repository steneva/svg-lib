#pragma once
#include <exception>
#include <string>

class PropertyParseException : public std::exception
{
public:
	PropertyParseException(const std::string& property_name, const std::string& value)
		: exception(("Could not parse property of type " + property_name + " with value \"" + value + "\".").c_str())
	{
	}

	PropertyParseException(const std::string& value)
		: exception(("Could not parse value \"" + value + "\".").c_str())
	{
	}
};
