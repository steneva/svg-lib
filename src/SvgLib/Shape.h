#pragma once

#include "Tag.h"
#include "DomElement.h"
#include "Length.h"
#include "Boxable.h"

class Shape : public DomElement, public Boxable
{
private:
	int _id;

public:

	Shape(xml::Tag& tag)
		: DomElement(tag)
	{
		static int s_id = 1;
		this->_id = s_id++;
	}

	int id() const
	{
		return this->_id;
	}

	virtual void translate(Length x_delta, Length y_delta) = 0;

	virtual void print(std::ostream& ostream) const = 0;
};
