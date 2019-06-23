#pragma once
#include "Command.h"
#include "CommandParamsException.h"

class OpenCommand : public Command
{
private:
	const int PATH_INDEX = 1;
public:

	bool can_execute(const CommandContext& context) const override
	{
		return !context.is_file_open();
	}

	void execute(const CommandContext& context) const override
	{
		if(context.args_count() != 2)
		{
			throw CommandParamsException();
		}

		const std::string path = context.arg(PATH_INDEX);
		context.open_svg(path);
	}

	void onSuccess(const CommandContext& context) const override
	{
		context.out() << "Successfully opened file " << context.file_path() << "." << std::endl;
	}
};
