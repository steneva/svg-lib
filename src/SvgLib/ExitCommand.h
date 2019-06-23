#pragma once
#include "Command.h"

class ExitCommand: public Command
{
public:
	bool can_execute(const CommandContext& context) const override
	{
		return true;
	}

	void execute(const CommandContext& context) const override
	{
		exit(EXIT_SUCCESS);
	}
};
