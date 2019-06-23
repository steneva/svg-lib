#pragma once

#include "Tag.h"
#include "DomElement.h"
#include "Boundary.h"

class Region;

class Shape : public DomElement
{
private:
	int _id;

public:

	Shape(xml::Tag* tag)
		: DomElement(tag)
	{
		static int s_id = 1;
		this->_id = s_id++;
	}

	Shape(const Shape& other)
		: DomElement(other)
	{
		this->_id = other._id;
	}

	int id() const
	{
		return this->_id;
	}

	virtual Boundary boundary() const = 0;

	virtual void translate(const Vector& offset) = 0;

	virtual void print(std::ostream& ostream) const = 0;
};
