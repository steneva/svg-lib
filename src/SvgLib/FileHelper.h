#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "FileOpenException.h"

class FileHelper
{
	template<typename T>
	static T open_file(const std::string& path)
	{
		T stream = T(path);
		if (stream.fail())
		{
			throw FileOpenException(path);
		}

		return stream;
	}

public:

	static std::string read_file_content(const std::string &path)
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

	static void save(const std::string &path, const std::string &content)
	{
		std::ofstream file(path, std::ofstream::out | std::ofstream::trunc);
		if(file.fail())
		{
			throw std::runtime_error("Could not save file.");
		}

		file << content;
	}
};
