#include "Circle.h"

Circle::Circle(xml::Tag* tag): Shape(tag)
{
}

Circle::Circle(const Circle& other): Shape(other)
{
}

void Circle::fill(Color value)
{
	set<Color>("fill", value);
}

Color Circle::fill() const
{
	return get<Color>("fill");
}

void Circle::radius(Length value)
{
	set<Length>("r", value);
}

Length Circle::radius() const
{
	return get<Length>("r");
}

void Circle::center(Point value)
{
	set<Coordinate>("cx", value.x);
	set<Coordinate>("cy", value.y);
}

Point Circle::center() const
{
	const Coordinate center_x = get<Coordinate>("cx");
	const Coordinate center_y = get<Coordinate>("cy");

	return Point(center_x, center_y);
}

DomElement* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::print(std::ostream& out) const
{
	out << id() << " " << tag()->name() << " " << center() << " " << radius() << " " << fill() << std::endl;
}

void Circle::translate(const Vector& offset)
{
	center(center() + offset);
}

Boundary Circle::boundary() const
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
