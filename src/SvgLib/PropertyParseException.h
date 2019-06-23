#pragma once
#include <exception>
#include <string>

class PropertyParseException : public std::exception
{
public:
	PropertyParseException(const std::string& property_name, const std::string& value);

	PropertyParseException(const std::string& value);
};
