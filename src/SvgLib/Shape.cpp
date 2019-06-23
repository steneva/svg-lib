#include "Shape.h"

Shape::Shape(xml::Tag* tag): DomElement(tag)
{
	static int s_id = 1;
	this->_id = s_id++;
}

Shape::Shape(const Shape& other): DomElement(other)
{
	this->_id = other._id;
}

int Shape::id() const
{
	return this->_id;
}
