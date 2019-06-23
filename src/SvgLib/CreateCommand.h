#pragma once
#include "Command.h"
#include "Color.h"
#include "Rectangle.h"
#include "Line.h"
#include "Circle.h"
#include<string>
#include "CommandParamsException.h"
#include "Property.h"

class CreateCommand : public Command
{
private:
	const struct
	{
		std::string RECTANGLE = "rectangle";
		std::string CIRCLE = "circle";
		std::string LINE = "line";
	} SHAPE_NAMES;

	static void create_rectangle(const CommandContext& context);

	static void create_circle(const CommandContext& context);

	static void create_line(const CommandContext& context);

public:
	bool can_execute(const CommandContext& context) const override;

	void execute(const CommandContext& context) const override;

	void onSuccess(const CommandContext& context) const override;
};
