#pragma once
#include "ScalableVectorGraphic.h"
#include<iostream>
#include <vector>

class Engine;

struct CommandContext
{
private:
	const std::vector<std::string> _args;
	Engine& _owner;

public:

	CommandContext(const std::vector<std::string>& args, Engine& owner);

	void open_svg();
	ScalableVectorGraphic* svg() const;
	std::ostream& out() const;
	std::string arg(int index) const;
	int arg_count() const;
};