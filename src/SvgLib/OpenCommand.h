#pragma once
#include "Command.h"
#include "CommandParamsException.h"

class OpenCommand : public Command
{
private:
	const int PATH_INDEX = 1;
public:

	bool can_execute(const CommandContext& context) const override;

	void execute(const CommandContext& context) const override;

	void onSuccess(const CommandContext& context) const override;
};
