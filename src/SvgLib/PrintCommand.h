#pragma once
#include "Command.h"
#include "CommandContext.h"
#include "CommandParamsException.h"

class PrintCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override;

	void execute(const CommandContext& context) const override;
};
