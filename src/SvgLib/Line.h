#pragma once
#include "Shape.h"
#include "Parser.h"

class Line : public Shape
{
private:
public:
	Line(xml::Tag& tag)
		: Shape(tag)
	{
	}

	DomElement* clone() const override
	{
		return new Line(*this);
	}

	void print(std::ostream &ostream) const override
	{
		// TODO: ilent
	}

	void translate(Length x_delta, Length y_delta) override
	{
		// TODO: ilent
	}

	Length leftmost() const override
	{
		// TODO: implement
		return Length(0);
	}

	Length rightmost() const override
	{
		// TODO: implement
		return Length(0);
	}

	Length topmost() const override
	{
		// TODO: implement
		return Length(0);
	}

	Length downmost() const override
	{
		// TODO: implement
		return Length(0);
	}
};
