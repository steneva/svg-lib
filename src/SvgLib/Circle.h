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

	Circle(xml::Tag* tag);

	Circle(const Circle& other);

	void fill(Color value);

	Color fill() const;

	void radius(Length value);

	Length radius() const;

	void center(Point value);

	Point center() const;

	DomElement* clone() const override;

	void print(std::ostream& out) const override;

	void translate(const Vector& offset) override;

	Boundary boundary() const override;
};
