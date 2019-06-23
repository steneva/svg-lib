#include "SaveCommand.h"

bool SaveCommand::can_execute(const CommandContext& context) const
{
	return context.is_file_open();
}

void SaveCommand::execute(const CommandContext& context) const
{
	std::string path;
	switch (context.args_count())
	{
		case 1:
		{
			path = context.file_path();
			break;
		}
		case 2:
		{
			path = context.arg(1);
			break;
		}
		default:
		{
			throw CommandParamsException();
		}
	}

	const std::string content = context.svg()->to_xml();
	FileHelper::save(path, content);
}

void SaveCommand::onSuccess(const CommandContext& context) const
{
	context.out() << "Successfully saved file." << std::endl;
}
