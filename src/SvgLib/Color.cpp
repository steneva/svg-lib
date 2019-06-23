#include "Color.h"

void Color::parse_impl(const std::string& value)
{
	this->value = value;
}

Color::Color(): value("black")
{
}

Color::Color(const std::string& color)
{
	this->value = color;
}

void Color::to_string_impl(std::ostream& out) const
{
	out << value;
}
