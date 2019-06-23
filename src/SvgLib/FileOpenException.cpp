#include "FileOpenException.h"

FileOpenException::FileOpenException(const std::string& path): exception(
	("Could not open file at location " + path + ".").c_str())
{
}
