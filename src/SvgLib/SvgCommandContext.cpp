#include "CommandContext.h"
#include "Engine.h"

CommandContext::CommandContext(const std::vector<std::string>& args, Engine& owner)
	:_args(args),_owner(owner)
{

}

void CommandContext::open_svg()
{

}

ScalableVectorGraphic* CommandContext::svg() const
{
	return this->_owner.svg();
}

std::ostream& CommandContext::out() const
{
	return this->_owner.out();
}

std::string CommandContext::arg(int index) const
{
	return this->_args[index];
}

int CommandContext::arg_count() const
{
	return this->_args.size();
}

void open_svg(const xml::Tag& xml_tree)
{

}