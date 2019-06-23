#pragma once
#include "Shape.h"
#include "Coordinate.h"
#include "Color.h"
#include "Point.h"
#include "Length.h"

class Rectangle : public Shape
{
public:
	Rectangle(xml::Tag* tag): Shape(tag)
	{
	}

	Rectangle(const Rectangle& other)
		: Shape(other)
	{
	}

	DomElement* clone() const override
	{
		return new Rectangle(*this);
	}

	Point origin() const
	{
		Coordinate x = this->get<Coordinate>("x");
		Coordinate y = this->get<Coordinate>("y");

		return Point(x, y);
	}

	void origin(Point value)
	{
		this->set<Coordinate>("x", value.x);
		this->set<Coordinate>("y", value.y);
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
		return this->set<Color>("fill", value);
	}

	void print(std::ostream& ostream) const override
	{
		ostream << id() << " " << tag()->name() << " " << origin() << " " <<
			width() << " " << height() << " " <<
			fill() << std::endl;
	}

	Boundary boundary() const override
	{
		const Point origin = this->origin();

		const Coordinate leftmost = std::min(origin.x, origin.x + width());
		const Coordinate rightmost = std::max(origin.x, origin.x + width());
		const Coordinate topmost = std::min(origin.y, origin.y + height());
		const Coordinate downmost = std::max(origin.y, origin.y + height());

		const Point top_left_corner(leftmost, topmost);
		const Point top_right_corner(rightmost, topmost);
		const Point bottom_left_corner(leftmost, downmost);
		const Point bottom_right_corner(rightmost, downmost);

		const std::vector<Point> boundaries = {
			top_left_corner,
			top_right_corner,
			bottom_left_corner,
			bottom_right_corner
		};

		return Boundary(boundaries);
	}

	void translate(const Vector& offset) override
	{
		origin(origin() + offset);
	}
};
