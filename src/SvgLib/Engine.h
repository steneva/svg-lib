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

	static std::vector<std::string> get_command_args(std::string command)
	{
		std::vector<std::string> args;

		std::istringstream stream(command);
		while (!stream.eof())
		{
			std::string arg;
			stream >> arg;
			args.push_back(arg);
		}

		return args;
	}

public:
	Engine(std::istream& in, std::ostream& out)
		: _in(in), _out(out)
	{
		_commands = {
			{COMMANDS.OPEN, new OpenCommand()},
			{COMMANDS.SAVE, new SaveCommand()},
			{COMMANDS.CLOSE, new CloseCommand()},
			{COMMANDS.EXIT, new ExitCommand()},
			{COMMANDS.PRINT, new PrintCommand()},
			{COMMANDS.ERASE, new EraseCommand()},
			{COMMANDS.TRANSLATE, new TranslateCommand()},
			{COMMANDS.CREATE, new CreateCommand()},
			{COMMANDS.WITHIN, new WithinCommand()},
		};
	}

	~Engine()
	{
		for (const std::map<std::basic_string<char>, Command*>::value_type& cmd : _commands)
		{
			delete cmd.second;
		}

		_commands.clear();

		delete _svg;
		delete _root;
	}

	void command_loop()
	{
		while (true)
		{
			std::string command_line;
			_out << ">";
			std::getline(_in, command_line);
			std::vector<std::string> args = get_command_args(command_line);

			const std::string command_name = args[0];
			Command* command = _commands.find(command_name)->second;
			CommandContext context = CommandContext(args, *this);

			if (command->can_execute(context))
			{
				try
				{
					command->execute(context);
					command->onSuccess(context);
				}
				catch (std::exception& e)
				{
					_out << e.what() << std::endl;
				}
			}
			else
			{
				_out << "The command is not supported in this context." << std::endl;
			}

			_out << std::endl;
		}
	}

	ScalableVectorGraphic* svg() const
	{
		return _svg;
	}

	void open_svg(const std::string& path)
	{
		const std::string file_content = FileHelper::read_file_content(path);
		_root = new xml::Tag(xml::Parser::parse(file_content));
		_svg = new ScalableVectorGraphic(SvgLoader::load(*_root));
		_file_path = path;
	}

	void close_svg()
	{
		this->_file_path = "";
		delete _svg;
		delete _root;

		_svg = nullptr;
		_root = nullptr;
	}

	std::string filePath() const
	{
		return this->_file_path;
	}

	void run()
	{
		command_loop();
	}

	std::ostream& out() const
	{
		return _out;
	}
};
