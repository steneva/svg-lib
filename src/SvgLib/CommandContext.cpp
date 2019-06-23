#include "CommandContext.h"
#include "Engine.h"

CommandContext::CommandContext(const std::vector<std::string>& args, Engine& owner)
	: _args(args), _owner(owner)
{
}

void CommandContext::open_svg(const std::string& path) const
{
	this->_owner.open_svg(path);
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
	if (index >= args_count())
	{
		return "";
	}

	return this->_args.at(index);
}

int CommandContext::args_count() const
{
	return this->_args.size();
}

bool CommandContext::is_file_open() const
{
	return svg() != nullptr;
}

std::string CommandContext::file_path() const
{
	return _owner.filePath();
}

void CommandContext::close_file() const
{
	this->_owner.close_svg();
}

void open_svg(const xml::Tag& xml_tree)
{
}
