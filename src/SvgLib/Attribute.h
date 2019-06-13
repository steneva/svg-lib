#pragma once
#include <string>

struct Attribute
{
public:
	std::string name;
	std::string value;

	Attribute(std::string name, std::string value)
	{
		this->name = name;
		this->value = value;
	}
};
