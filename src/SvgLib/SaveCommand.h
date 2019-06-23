#pragma once
#include "Command.h"
#include "CommandParamsException.h"

class SaveCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override
	{
		return context.is_file_open();
	}

	void execute(const CommandContext& context) const override
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

	void onSuccess(const CommandContext& context) const override
	{
		context.out() << "Successfully saved file." << std::endl;
	}
};
