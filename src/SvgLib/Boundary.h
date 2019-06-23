#pragma once
#include "Point.h"
#include <vector>

class Boundary
{
private:
	std::vector<Point> points;

public:
	typedef std::vector<Point>::const_iterator const_iterator;

	Boundary(const std::vector<Point>& points);

	const_iterator begin() const;

	const_iterator end() const;
};
