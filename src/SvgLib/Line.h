#pragma once
#include "Shape.h"
#include "Parser.h"
#include "Color.h"

class Line final : public Shape
{
public:
	Line(xml::Tag* tag)
		: Shape(tag)
	{
	}

	Line(const Line& other)
		: Shape(other)
	{
	}

	Point start() const
	{
		const Coordinate x1 = this->get<Coordinate>("x1");
		const Coordinate y1 = this->get<Coordinate>("y1");

		return Point(x1, y1);
	}

	void start(Point value)
	{
		this->set<Coordinate>("x1", value.x);
		this->set<Coordinate>("y1", value.y);
	}

	Point end() const
	{
		const Coordinate x2 = this->get<Coordinate>("x2");
		const Coordinate y2 = this->get<Coordinate>("y2");

		return Point(x2, y2);
	}

	void end(Point value)
	{
		this->set<Coordinate>("x2", value.x);
		this->set<Coordinate>("y2", value.y);
	}

	Color stroke() const
	{
		return this->get<Color>("stroke");
	}

	void stroke(Color value)
	{
		return this->set<Color>("stroke", value);
	}

	Boundary boundary() const override
	{
		const std::vector<Point> boundaries =
		{
			start(),
			end(),
		};

		return Boundary(boundaries);
	}

	DomElement* clone() const override
	{
		return new Line(*this);
	}

	void print(std::ostream& ostream) const override
	{
		const Point start_point = start();
		const Point end_point = end();
		ostream << id() << " " << tag()->name() << " " <<
			start_point.x << " " << start_point.y << " " <<
			end_point.x << " " << end_point.y << " " <<
			stroke() << std::endl;
	}

	void translate(const Vector& offset) override
	{
		start(start() + offset);
		end(end() + offset);
	}
};
