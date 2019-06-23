#pragma once
#include <string>
#include"Coordinate.h"
#include "Length.h"
#include "PropertyParseException.h"
#include "Color.h"

class Property
{
	template <typename T>
	static T create(const std::string& value, const std::string& type_name)
	{
		T result;
		try
		{
			result.parse(value);
		}
		catch (...)
		{
			throw PropertyParseException(type_name, value);
		}

		return result;
	}

public:
	static Coordinate coordinate(const std::string& value);

	static Length length(const std::string& value);

	static Color color(const std::string& value);
};
