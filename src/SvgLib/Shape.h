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

	Shape(xml::Tag* tag);

	Shape(const Shape& other);

	int id() const;

	virtual Boundary boundary() const = 0;

	virtual void translate(const Vector& offset) = 0;

	virtual void print(std::ostream& ostream) const = 0;
};
