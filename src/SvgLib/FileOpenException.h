#pragma once
#include <string>
#include <exception>

class FileOpenException : public std::exception
{
public:
	FileOpenException(const std::string& path)
		: exception(("Could not open file at location " + path + ".").c_str())
	{
	}
};
