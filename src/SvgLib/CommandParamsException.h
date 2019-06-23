#pragma once
#include <exception>

class CommandParamsException : public std::exception
{
public:
	CommandParamsException();
};
