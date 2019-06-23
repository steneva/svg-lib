#pragma once
#include "Shape.h"
#include "Coordinate.h"
#include "Color.h"
#include <iomanip>
#include "Point.h"
#include "Length.h"

class Circle : public Shape
{
public:

	Circle(xml::Tag* tag) : Shape(tag)
	{
	}

	Circle(const Circle& other)
		: Shape(other)
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

	void center(Point value)
	{
		set<Coordinate>("cx", value.x);
		set<Coordinate>("cy", value.y);
	}

	Point center() const
	{
		const Coordinate center_x = get<Coordinate>("cx");
		const Coordinate center_y = get<Coordinate>("cy");

		return Point(center_x, center_y);
	}

	DomElement* clone() const override
	{
		return new Circle(*this);
	}

	void print(std::ostream& out) const override
	{
		out << id() << " " << tag()->name() << " " << center() << " " << radius() << " " << fill() << std::endl;
	}

	void translate(const Vector& offset) override
	{
		center(center() + offset);
	}

	Boundary boundary() const override
	{
		const Coordinate y_min = std::min(center().y - radius(), center().y + radius());
		const Coordinate y_max = std::max(center().y - radius(), center().y + radius());
		const Coordinate x_min = std::min(center().x - radius(), center().x + radius());
		const Coordinate x_max = std::min(center().x - radius(), center().x + radius());

		const Point top(center().x, y_min);
		const Point bottom(center().x, y_max);
		const Point left(x_min, center().y);
		const Point right(x_max, center().y);

		return Boundary({top, bottom, left, right});
	}
};
