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

	static std::string read_file_content(const std::string& path);

	static void write_file_content(const std::string& path, const std::string& content);

	static void save(const std::string& path, const std::string& content);
};
