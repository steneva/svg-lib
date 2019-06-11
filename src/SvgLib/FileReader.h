#pragma once
#include <string>
#include <fstream>

class FileReader
{
public:
	static std::string get_file_content(std::string path)
	{
		std::ifstream file(path);
		if (file.fail())
		{
			throw std::runtime_error("Could not open file.");
		}

		std::string content;

		std::string line;
		while (std::getline(file, line))
		{
			content += line;
			content.push_back('\n');
		}

		return content;
	}
};
