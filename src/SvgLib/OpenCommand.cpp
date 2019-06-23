#include "OpenCommand.h"

bool OpenCommand::can_execute(const CommandContext& context) const
{
	return !context.is_file_open();
}

void OpenCommand::execute(const CommandContext& context) const
{
	if (context.args_count() != 2)
	{
		throw CommandParamsException();
	}

	const std::string path = context.arg(PATH_INDEX);
	context.open_svg(path);
}

void OpenCommand::onSuccess(const CommandContext& context) const
{
	context.out() << "Successfully opened file " << context.file_path() << "." << std::endl;
}
