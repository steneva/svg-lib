#include "CloseCommand.h"

bool CloseCommand::can_execute(const CommandContext& context) const
{
	return context.is_file_open();
}

void CloseCommand::execute(const CommandContext& context) const
{
	context.close_file();
}

void CloseCommand::onSuccess(const CommandContext& context) const
{
	context.out() << "Successfully closed file." << std::endl;
}
