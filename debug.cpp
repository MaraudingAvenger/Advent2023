#include "debug.h"

#include <iostream>

/*
debugger.log(std::string message)

logs a message to the console with the format:
	[debugger name] message
*/
void debug::Debug::log(const std::string& message)
{
	if (!_enabled) return;
	std::cout << "[" << this->_name << "] " << message << std::endl;
}

/*
debugger.warn(std::string message)

logs a warning message to the console with the format:
	[debugger name] WARNING: message

and colors the text yellow
*/
void debug::Debug::warn(const std::string& message)
{
	if (!_enabled) return;
	std::cout << "\033[33m[" << this->_name << "] WARNING: " << message << "\033[0m" << std::endl;
}

/*
debugger.error(std::string message)

logs an error message to the console with the format:
	[debugger name] ERROR: message

and colors the text red
*/
void debug::Debug::error(const std::string& message)
{
	if (!_enabled) return;
	std::cout << "\033[31m[" << this->_name << "] ERROR: " << message << "\033[0m" << std::endl;
}

/*
debugger.info(std::string message)

logs an informational message to the console with the format:
	[debugger name] INFO: message

and colors the text blue
*/
void debug::Debug::info(const std::string& message)
{
	if (!_enabled) return;
	std::cout << "\033[34m[" << this->_name << "] INFO: " << message << "\033[0m" << std::endl;
}