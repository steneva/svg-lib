#pragma once
#include <string>
#include <fstream>
#include <sstream>

class FileHelper
{
	template<typename T>
	static T open_file(const std::string& path)
	{
		T stream = T(path);
		if (stream.fail())
		{
			throw std::runtime_error("Could not open file.");
		}
		return stream;
	}

public:

	static std::string read_file_content(std::string path)
	{
		auto file = open_file<std::ifstream>(path);
		std::stringstream sstream;
		
		std::string line;
		while (std::getline(file, line))
		{
			sstream<<line<< std::endl;
		}

		return sstream.str();
	}

	static void write_file_content(const std::string& path, const std::string& content)
	{
		auto file = open_file<std::ofstream>(path);

		file << path << std::endl;
	}
};
