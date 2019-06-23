#pragma once
#include "ScalableVectorGraphic.h"
#include<iostream>
#include <vector>
#include "FileHelper.h"

class Engine;

struct CommandContext
{
private:
	const std::vector<std::string> _args;
	Engine& _owner;
	std::string _filePath;

public:

	void open_svg(const std::string &path) const;

	ScalableVectorGraphic* svg() const;

	std::ostream& out() const;

	std::string arg(int index) const;

	int args_count() const;

	bool is_file_open() const;

	std::string file_path() const;

	void close_file() const;

	CommandContext(const std::vector<std::string>& args, Engine& owner);
};