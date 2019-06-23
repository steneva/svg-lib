#pragma once
#include "Point.h"
#include <vector>

class Boundary
{
private:
	std::vector<Point> points;

public:
	typedef std::vector<Point>::const_iterator const_iterator;

	Boundary(const std::vector<Point>& points)
	{
		this->points = points;
	}

	const_iterator begin() const
	{
		return points.begin();
	}

	const_iterator end() const
	{
		return points.end();
	}
};
