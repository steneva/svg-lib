#include "FileHelper.h"

std::string FileHelper::read_file_content(const std::string& path)
{
	auto file = open_file<std::ifstream>(path);
	std::stringstream sstream;

	std::string line;
	while (std::getline(file, line))
	{
		sstream << line << std::endl;
	}

	return sstream.str();
}

void FileHelper::write_file_content(const std::string& path, const std::string& content)
{
	auto file = open_file<std::ofstream>(path);

	file << path << std::endl;
}

void FileHelper::save(const std::string& path, const std::string& content)
{
	std::ofstream file(path, std::ofstream::out | std::ofstream::trunc);
	if (file.fail())
	{
		throw std::runtime_error("Could not save file.");
	}

	file << content;
}
