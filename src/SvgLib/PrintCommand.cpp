#include "PrintCommand.h"

bool PrintCommand::can_execute(const CommandContext& context) const
{
	return context.svg() != nullptr;
}

void PrintCommand::execute(const CommandContext& context) const
{
	if (context.args_count() != 1)
	{
		throw CommandParamsException();
	}

	context.svg()->print(context.out());
}
