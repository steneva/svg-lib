#pragma once
#include "Command.h"
#include "Property.h"
#include "RectangleRegion.h"
#include "CircleRegion.h"
#include "CommandParamsException.h"

class WithinCommand : public Command
{
private:
	static RectangleRegion* create_rectangle_region(const CommandContext& context);

	static CircleRegion* create_circle_region(const CommandContext& context);

public:
	bool can_execute(const CommandContext& context) const override;

	void execute(const CommandContext& context) const override;
};
