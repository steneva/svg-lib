#pragma once
#include "Command.h"
#include "CommandParamsException.h"

class SaveCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override;

	void execute(const CommandContext& context) const override;

	void onSuccess(const CommandContext& context) const override;
};
