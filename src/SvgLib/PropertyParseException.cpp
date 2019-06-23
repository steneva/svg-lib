#include "PropertyParseException.h"

PropertyParseException::PropertyParseException(const std::string& property_name, const std::string& value): exception(
	("Could not parse property of type " + property_name + " with value \"" + value + "\".").c_str())
{
}

PropertyParseException::PropertyParseException(const std::string& value): exception(
	("Could not parse value \"" + value + "\".").c_str())
{
}
