#pragma once

#include <string>
#include <ostream>
#include <sstream>

struct PropertyValue
{
protected:
	virtual void to_string_impl(std::ostream& out) const = 0;

public:
	virtual ~PropertyValue() = default;

	virtual void parse(const std::string& value) = 0;

	virtual std::string to_string() const 
	{
		std::ostringstream out;
		to_string_impl(out);
		return out.str();
	}

	friend std::ostream& operator<<(std::ostream& out, const PropertyValue& value)
	{
		out << value.to_string();
		return out;
	}
};
