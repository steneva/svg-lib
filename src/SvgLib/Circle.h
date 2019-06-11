#pragma once
#include "Shape.h"
#include "Length.h"
#include "Color.h"
#include <iomanip>

class Circle : public Shape
{
public:

	Circle(xml::Tag& tag) : Shape(tag)
	{

	}

	void fill(Color value)
	{
		set<Color>("fill", value);
	}

	Color fill() const
	{
		return get<Color>("fill");
	}

	void radius(Length value)
	{
		set<Length>("r", value);
	}

	Length radius() const
	{
		return get<Length>("r");
	}

	void center_y(Length value)
	{
		set<Length>("cy", value);
	}

	Length center_y() const
	{
		return get<Length>("cy");
	}

	void center_x(Length value)
	{
		set<Length>("cx", value);
	}

	Length center_x() const
	{
		return get<Length>("cx");
	}

	DomElement* clone() const override
	{
		return new Circle(*this);
	}

	void print(std::ostream &out) const override
	{
		out << id() <<" "<< tag()->name() << " " << center_x() << " " << 
			center_y() << " "<< radius() <<" " << fill() << std::endl;
	}

	void translate(Length x, Length y) override
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
