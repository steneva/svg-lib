#include "Engine.h"

std::vector<std::string> Engine::get_command_args(std::string command)
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

Engine::Engine(std::istream& in, std::ostream& out): _in(in), _out(out)
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

Engine::~Engine()
{
	for (const std::map<std::basic_string<char>, Command*>::value_type& cmd : _commands)
	{
		delete cmd.second;
	}

	_commands.clear();

	delete _svg;
	delete _root;
}

void Engine::command_loop()
{
	while (true)
	{
		std::string command_line;
		_out << ">";
		std::getline(_in, command_line);
		std::vector<std::string> args = get_command_args(command_line);

		const std::string command_name = args[0];

		std::map<std::basic_string<char>, Command*>::iterator command_result = _commands.find(command_name);

		if (command_result == _commands.end())
		{
			std::cout << "Unrecognized command." << std::endl;
			continue;
		}

		Command* command = command_result->second;
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

ScalableVectorGraphic* Engine::svg() const
{
	return _svg;
}

void Engine::open_svg(const std::string& path)
{
	const std::string file_content = FileHelper::read_file_content(path);
	_root = new xml::Tag(xml::Parser::parse(file_content));
	_svg = new ScalableVectorGraphic(SvgLoader::load(*_root));
	_file_path = path;
}

void Engine::close_svg()
{
	this->_file_path = "";
	delete _svg;
	delete _root;

	_svg = nullptr;
	_root = nullptr;
}

std::string Engine::filePath() const
{
	return this->_file_path;
}

void Engine::run()
{
	command_loop();
}

std::ostream& Engine::out() const
{
	return _out;
}
