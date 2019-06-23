#pragma once
#include "Command.h"
#include "CommandParamsException.h"

class EraseCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override;

	void execute(const CommandContext& context) const override;

	void onSuccess(const CommandContext& context) const override;
};
