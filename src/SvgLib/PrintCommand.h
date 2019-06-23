#pragma once
#include "Command.h"
#include "CommandContext.h"
#include "CommandParamsException.h"

class PrintCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override
	{
		return context.svg() != nullptr;
	}

	void execute(const CommandContext& context) const override
	{
		if (context.args_count() != 1)
		{
			throw CommandParamsException();
		}

		context.svg()->print(context.out());
	}
};
