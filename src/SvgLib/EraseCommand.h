#pragma once
#include "Command.h"
#include "CommandParamsException.h"

class EraseCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override
	{
		return context.svg() != nullptr;
	}

	void execute(const CommandContext& context) const override
	{
		if (context.args_count() != 2)
		{
			throw CommandParamsException();
		}

		std::string id_text = context.arg(1);
		const bool is_number = !id_text.empty()
			&& id_text.find_first_not_of("0123456789") == std::string::npos;

		if (!is_number)
		{
			throw std::runtime_error("Invalid id.");
		}

		const int id = std::stoi(id_text);
		context.svg()->erase(id);
	}

	void onSuccess(const CommandContext& context) const override
	{
		context.out() << "Successfully erased shape." << std::endl;
	}
};
