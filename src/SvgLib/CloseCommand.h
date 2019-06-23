#pragma once
#include "Command.h"

class CloseCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override
	{
		return context.is_file_open();
	}

	void execute(const CommandContext& context) const override
	{
		context.close_file();
	}

	void onSuccess(const CommandContext& context) const override
	{
		context.out() << "Successfully closed file." << std::endl;
	}
};
