#include "Line.h"

Line::Line(xml::Tag* tag): Shape(tag)
{
}

Line::Line(const Line& other): Shape(other)
{
}

Point Line::start() const
{
	const Coordinate x1 = this->get<Coordinate>("x1");
	const Coordinate y1 = this->get<Coordinate>("y1");

	return Point(x1, y1);
}

void Line::start(Point value)
{
	this->set<Coordinate>("x1", value.x);
	this->set<Coordinate>("y1", value.y);
}

Point Line::end() const
{
	const Coordinate x2 = this->get<Coordinate>("x2");
	const Coordinate y2 = this->get<Coordinate>("y2");

	return Point(x2, y2);
}

void Line::end(Point value)
{
	this->set<Coordinate>("x2", value.x);
	this->set<Coordinate>("y2", value.y);
}

Color Line::stroke() const
{
	return this->get<Color>("stroke");
}

void Line::stroke(Color value)
{
	return this->set<Color>("stroke", value);
}

Boundary Line::boundary() const
{
	const std::vector<Point> boundaries =
	{
		start(),
		end(),
	};

	return Boundary(boundaries);
}

DomElement* Line::clone() const
{
	return new Line(*this);
}

void Line::print(std::ostream& ostream) const
{
	const Point start_point = start();
	const Point end_point = end();
	ostream << id() << " " << tag()->name() << " " <<
		start_point.x << " " << start_point.y << " " <<
		end_point.x << " " << end_point.y << " " <<
		stroke() << std::endl;
}

void Line::translate(const Vector& offset)
{
	start(start() + offset);
	end(end() + offset);
}
