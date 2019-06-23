#pragma once
#include "Shape.h"
#include "Coordinate.h"
#include "Color.h"
#include "Point.h"
#include "Length.h"

class Rectangle : public Shape
{
public:
	Rectangle(xml::Tag* tag);

	Rectangle(const Rectangle& other);

	DomElement* clone() const override;

	Point origin() const;

	void origin(Point value);

	Length width() const;

	void width(Length value);

	Length height() const;

	void height(Length value);

	Color fill() const;

	void fill(Color value);

	void print(std::ostream& ostream) const override;

	Boundary boundary() const override;

	void translate(const Vector& offset) override;
};
