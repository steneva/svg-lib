#pragma once

#include "CommandContext.h"

class Command
{
public:
	virtual ~Command();

	virtual bool can_execute(const CommandContext& context) const = 0;

	virtual void execute(const CommandContext& context) const = 0;

	virtual void onSuccess(const CommandContext& context) const;;
};
