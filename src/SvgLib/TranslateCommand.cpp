#include "TranslateCommand.h"

bool TranslateCommand::can_execute(const CommandContext& context) const
{
	return context.svg() != nullptr;
}

void TranslateCommand::execute(const CommandContext& context) const
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

void TranslateCommand::onSuccess(const CommandContext& context) const
{
	context.out() << "Successfully translated shapes." << std::endl;
}
