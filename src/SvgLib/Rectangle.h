#pragma once
#include "Shape.h"
#include "Length.h"
#include "Color.h"

class Rectangle : public Shape
{
public:
	Rectangle(xml::Tag& tag): Shape(tag)
	{
	}

	DomElement* clone() const override
	{
		return new Rectangle(*this);
	}

	Length x() const
	{
		return this->get<Length>("x");
	}

	void x(Length value)
	{
		this->set("x", value);
	}

	Length y() const
	{
		return this->get<Length>("y");
	}

	void y(Length value)
	{
		this->set("y", value);
	}

	Length width() const
	{
		return this->get<Length>("width");
	}

	void width(Length value)
	{
		this->set("width", value);
	}

	Length height() const
	{
		return this->get<Length>("height");
	}

	void height(Length value)
	{
		this->set("height", value);
	}

	Color fill() const
	{
		return this->get<Color>("fill");
	}

	void fill(Color value)
	{
		return this->set<Color>("color", value);
	}

	void print(std::ostream& ostream) const override
	{
		ostream << id() << " " << tag()->name() << " " <<
			x() << " " << y() << " " <<
			width() << " " << height() << " " <<
			fill() << std::endl;
	}

	void translate(Length x_delta, Length y_delta) override
	{
		x(x() + x_delta);
		y(y() + y_delta);
	}

	Length leftmost() const override
	{
		return std::min(x(), x() + width());
	}

	Length rightmost() const override
	{
		return std::max(x(), x() + width());
	}

	Length topmost() const override
	{
		return std::min(x(), x() + height());
	}

	Length downmost() const override
	{
		return std::max(x(), x() + height());
	}
};
