#pragma once

#include <string>
#include <ostream>
#include <sstream>
#include "PropertyParseException.h"

struct PropertyValue
{
protected:
	virtual void to_string_impl(std::ostream& out) const = 0;
	virtual void parse_impl(const std::string& value) = 0;

public:
	virtual ~PropertyValue() = default;

	virtual void parse(const std::string& value);

	virtual std::string to_string() const;

	friend std::ostream& operator<<(std::ostream& out, const PropertyValue& value);
};
