#include "ExitCommand.h"

bool ExitCommand::can_execute(const CommandContext& context) const
{
	return true;
}

void ExitCommand::execute(const CommandContext& context) const
{
	exit(EXIT_SUCCESS);
}
