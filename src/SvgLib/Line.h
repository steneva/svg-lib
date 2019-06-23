#pragma once
#include "Shape.h"
#include "Parser.h"
#include "Color.h"

class Line final : public Shape
{
public:
	Line(xml::Tag* tag);

	Line(const Line& other);

	Point start() const;

	void start(Point value);

	Point end() const;

	void end(Point value);

	Color stroke() const;

	void stroke(Color value);

	Boundary boundary() const override;

	DomElement* clone() const override;

	void print(std::ostream& ostream) const override;

	void translate(const Vector& offset) override;
};
