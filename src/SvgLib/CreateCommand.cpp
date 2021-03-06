﻿#include "CreateCommand.h"

void CreateCommand::create_rectangle(const CommandContext& context)
{
	const Coordinate origin_x = Property::coordinate(context.arg(2));
	const Coordinate origin_y = Property::coordinate(context.arg(3));
	const Point origin(origin_x, origin_y);

	const Length width = Property::length(context.arg(4));
	const Length height = Property::length(context.arg(5));

	const Color fill = Property::color(context.arg(6));

	Rectangle* rectangle = context.svg()->create<Rectangle>();
	rectangle->origin(origin);
	rectangle->width(width);
	rectangle->height(height);
	rectangle->fill(fill);
}

void CreateCommand::create_circle(const CommandContext& context)
{
	const Coordinate center_x = Property::coordinate(context.arg(2));
	const Coordinate center_y = Property::coordinate(context.arg(3));
	const Point center(center_x, center_y);

	const Length radius = Property::length(context.arg(4));

	const Color fill = Property::color(context.arg(6));

	Circle* circle = context.svg()->create<Circle>();
	circle->center(center);
	circle->radius(radius);
	circle->fill(fill);
}

void CreateCommand::create_line(const CommandContext& context)
{
	const Coordinate first_x = Property::coordinate(context.arg(2));
	const Coordinate first_y = Property::coordinate(context.arg(3));
	const Point first(first_x, first_y);

	const Coordinate second_x = Property::coordinate(context.arg(4));
	const Coordinate second_y = Property::coordinate(context.arg(5));
	const Point second(second_x, second_y);

	Color stroke;
	stroke.parse(context.arg(6));

	Line* line = context.svg()->create<Line>();
	line->start(first);
	line->end(second);
	line->stroke(stroke);
}

bool CreateCommand::can_execute(const CommandContext& context) const
{
	return context.svg() != nullptr;
}

void CreateCommand::execute(const CommandContext& context) const
{
	const std::string shape_name = context.arg(1);

	if (shape_name == SHAPE_NAMES.RECTANGLE)
	{
		if (context.args_count() < 6)
		{
			throw CommandParamsException();
		}

		create_rectangle(context);
	}
	else if (shape_name == SHAPE_NAMES.CIRCLE)
	{
		if (context.args_count() < 5)
		{
			throw CommandParamsException();
		}

		create_circle(context);
	}
	else if (shape_name == SHAPE_NAMES.LINE)
	{
		if (context.args_count() < 6)
		{
			throw CommandParamsException();
		}

		create_line(context);
	}
	else
	{
		throw std::runtime_error("Invalid or unsupported shape name.");
	}
}

void CreateCommand::onSuccess(const CommandContext& context) const
{
	context.out() << "Successfully created shape." << std::endl;
}
