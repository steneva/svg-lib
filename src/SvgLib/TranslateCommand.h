#pragma once
#include "Command.h"
#include "Property.h"
#include "CommandParamsException.h"

class TranslateCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override
	{
		return context.svg() != nullptr;
	}

	void execute(const CommandContext& context) const override
	{
		if (context.args_count() < 3 || context.args_count() > 4)
		{
			throw CommandParamsException();
		}

		const int args_length = context.args_count();

		const Length x_delta = Property::length(context.arg(args_length - 2));
		const Length y_delta = Property::length((context.arg(args_length - 1)));

		const Vector offset(x_delta, y_delta);

		if (args_length == 4)
		{
			const int id = std::stoi(context.arg(1));
			context.svg()->translate(id, offset);
			return;
		}

		context.svg()->translate(offset);
	}

	void onSuccess(const CommandContext& context) const override
	{
		context.out() << "Successfully translated shapes." << std::endl;
	}
};
