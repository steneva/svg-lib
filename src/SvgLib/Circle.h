#pragma once
#include "Shape.h"
#include "Length.h"
#include "Color.h"
#include <iomanip>
#include "Point.h"

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

	void center(Point value)
	{
		this->center_x(value.x);
		this->center_y(value.y);
	}

	Point center() const
	{
		return Point(center_x(), center_y());
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
		Point current_center = center();
		current_center.x += x;
		current_center.y += y;
		center(current_center);
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
