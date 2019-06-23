#pragma once
#include "Command.h"
#include "Property.h"
#include "CommandParamsException.h"

class TranslateCommand : public Command
{
public:
	bool can_execute(const CommandContext& context) const override;

	void execute(const CommandContext& context) const override;

	void onSuccess(const CommandContext& context) const override;
};
