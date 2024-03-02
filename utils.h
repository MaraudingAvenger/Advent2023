#ifndef ADVENT2023_UTILS_H
#define ADVENT2023_UTILS_H

#include <string>
#include <vector>
namespace utils
{
	std::vector<std::string> split(const std::string& str);
	std::vector<std::string> split(const std::string& str, const std::string& delim);
	std::vector<std::string> split(const std::string& str, const char delim);
	std::string trim(const std::string& str);
	std::string trim(const std::string& str, const std::string& chars);
	std::string join(const std::vector<std::string>& vec, const std::string& delim);
	std::string join(const std::vector<std::string>& vec, const char delim);
	std::string replace(const std::string& str, const std::string& from, const std::string& to);
	std::string replace(const std::string& str, const char from, const char to);
	std::vector<std::string> get_files(const std::string& dir, const std::string& ext);
	std::string filter(const std::string& str, const std::string& chars);
	std::string digits(const std::string& str);
	std::string letters(const std::string& str);
}

#endif // ADVENT2023_UTILS_H