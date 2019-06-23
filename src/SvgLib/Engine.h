#pragma once
#include <string>
#include <vector>
#include "Command.h"
#include <map>
#include "PrintCommand.h"
#include "EraseCommand.h"
#include "TranslateCommand.h"
#include "WithinCommand.h"
#include "Parser.h"
#include "FileHelper.h"
#include "SvgLoader.h"
#include "OpenCommand.h"
#include "CreateCommand.h"
#include "SaveCommand.h"
#include "CloseCommand.h"
#include "ExitCommand.h"

class Engine
{
	struct
	{
		const std::string OPEN = "open";
		const std::string CLOSE = "close";
		const std::string EXIT = "exit";
		const std::string SAVE = "save";
		const std::string PRINT = "print";
		const std::string ERASE = "erase";
		const std::string TRANSLATE = "translate";
		const std::string CREATE = "create";
		const std::string WITHIN = "within";
	} COMMANDS;

private:
	std::istream& _in;
	std::ostream& _out;
	std::map<std::string, Command*> _commands;
	ScalableVectorGraphic* _svg = nullptr;
	xml::Tag* _root = nullptr;
	std::string _file_path;

	static std::vector<std::string> get_command_args(std::string command);

public:
	Engine(std::istream& in, std::ostream& out);

	~Engine();

	void command_loop();

	ScalableVectorGraphic* svg() const;

	void open_svg(const std::string& path);

	void close_svg();

	std::string filePath() const;

	void run();

	std::ostream& out() const;
};
