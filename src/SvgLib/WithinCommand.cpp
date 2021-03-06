﻿#include "WithinCommand.h"

RectangleRegion* WithinCommand::create_rectangle_region(const CommandContext& context)
{
	const Coordinate x = Property::coordinate(context.arg(2));
	const Coordinate y = Property::coordinate(context.arg(3));

	const Length width = Property::length(context.arg(4));
	const Length height = Property::length(context.arg(5));

	return new RectangleRegion(x, y, width, height);
}

CircleRegion* WithinCommand::create_circle_region(const CommandContext& context)
{
	const Coordinate center_x = Property::coordinate(context.arg(2));
	const Coordinate center_y = Property::coordinate(context.arg(3));

	const Length radius = Property::length(context.arg(4));

	return new CircleRegion(center_x, center_y, radius);
}

bool WithinCommand::can_execute(const CommandContext& context) const
{
	return context.svg() != nullptr;
}

void WithinCommand::execute(const CommandContext& context) const
{
	if (context.args_count() < 5 || context.args_count() > 6)
	{
		throw CommandParamsException();
	}

	Region* region = nullptr;

	const std::string region_name = context.arg(1);
	if (region_name == "rectangle")
	{
		region = create_rectangle_region(context);
	}
	else if (region_name == "circle")
	{
		region = create_circle_region(context);
	}
	else
	{
		throw std::runtime_error("Region is not supported.");
	}

	std::vector<Shape*> shapes = context.svg()->shapes_within(region);
	if (shapes.empty())
	{
		context.out() << "None of the shapes are within this region." << std::endl;
	}

	for (Shape* shape : shapes)
	{
		shape->print(context.out());
	}
}
