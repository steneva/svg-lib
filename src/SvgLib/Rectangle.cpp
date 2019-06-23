#include "Rectangle.h"

Rectangle::Rectangle(xml::Tag* tag): Shape(tag)
{
}

Rectangle::Rectangle(const Rectangle& other): Shape(other)
{
}

DomElement* Rectangle::clone() const
{
	return new Rectangle(*this);
}

Point Rectangle::origin() const
{
	Coordinate x = this->get<Coordinate>("x");
	Coordinate y = this->get<Coordinate>("y");

	return Point(x, y);
}

void Rectangle::origin(Point value)
{
	this->set<Coordinate>("x", value.x);
	this->set<Coordinate>("y", value.y);
}

Length Rectangle::width() const
{
	return this->get<Length>("width");
}

void Rectangle::width(Length value)
{
	this->set("width", value);
}

Length Rectangle::height() const
{
	return this->get<Length>("height");
}

void Rectangle::height(Length value)
{
	this->set("height", value);
}

Color Rectangle::fill() const
{
	return this->get<Color>("fill");
}

void Rectangle::fill(Color value)
{
	return this->set<Color>("fill", value);
}

void Rectangle::print(std::ostream& ostream) const
{
	ostream << id() << " " << tag()->name() << " " << origin() << " " <<
		width() << " " << height() << " " <<
		fill() << std::endl;
}

Boundary Rectangle::boundary() const
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

void Rectangle::translate(const Vector& offset)
{
	origin(origin() + offset);
}
