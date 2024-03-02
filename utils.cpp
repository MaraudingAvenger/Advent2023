#include "utils.h"

#include <vector>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <string>

/*
split a string into a vector of strings, splitting on a whitespace

@param str: the string to split
@return: a vector of strings
*/
std::vector<std::string> utils::split(const std::string& str)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (ss >> token)
	{
		tokens.push_back(token);
	}
	return tokens;
}

/*
split a string into a vector of strings, splitting on a delimiter

@param str: the string to split
@param delim: the delimiter to split on
@return: a vector of strings
*/
std::vector<std::string> utils::split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

/*
split a string into a vector of strings, splitting on a delimiter

@param str: the string to split
@param delim: the delimiter to split on
@return: a vector of strings
*/
std::vector<std::string> utils::split(const std::string& str, const char delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim))
    {
        if (!token.empty())
            tokens.push_back(token);
    }
    return tokens;
}

/*
trim a string of whitespace from either end

@param str: the string to trim
@return: the trimmed string
*/
std::string utils::trim(const std::string& str)
{
    std::string s = str;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
        { return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
        { return !std::isspace(ch); })
        .base(),
        s.end());
    return s;
}

/*
trim a string of specific characters from either end

@param str: the string to trim
@param chars: the characters to trim
@return: the trimmed string
*/
std::string utils::trim(const std::string& str, const std::string& chars)
{
    std::string s = str;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [&chars](int ch)
        { return chars.find(ch) == std::string::npos; }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [&chars](int ch)
        { return chars.find(ch) == std::string::npos; })
        .base(),
        s.end());
    return s;
}

/*
join a vector of strings into a single string using a delimiter

@param vec: the vector of strings to join
@param delim: the delimiter to use
@return: the joined string
*/
std::string utils::join(const std::vector<std::string>& vec, const std::string& delim)
{
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        ss << vec[i];
        if (i != vec.size() - 1)
            ss << delim;
    }
    return ss.str();
}

/*
join a vector of strings into a single string using a delimiter

@param vec: the vector of strings to join
@param delim: the delimiter to use
@return: the joined string
*/
std::string utils::join(const std::vector<std::string>& vec, const char delim)
{
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        ss << vec[i];
        if (i != vec.size() - 1)
            ss << delim;
    }
    return ss.str();
}

/*
replace all occurrences of a character in a string with another character

@param str: the string to replace characters in
@param from: the characters to replace
@param to: the characters to replace with
@return: the string with the characters replaced
*/
std::string utils::replace(const std::string& str, const std::string& from, const std::string& to)
{
    std::string s = str;
    size_t start_pos = 0;
    while ((start_pos = s.find(from, start_pos)) != std::string::npos)
    {
        s.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return s;
}

/*
replace all occurrences of a character in a string with another character

@param str: the string to replace characters in
@param from: the character to replace
@param to: the character to replace with
@return: the string with the characters replaced
*/
std::string utils::replace(const std::string& str, const char from, const char to)
{
    std::string s = str;
    size_t start_pos = 0;
    while ((start_pos = s.find(from, start_pos)) != std::string::npos)
    {
        s.replace(start_pos, 1, 1, to);
        start_pos += 1;
    }
    return s;
}

/*
get the files in a directory with a specific extension

@param dir: the directory to search
@param ext: the extension to search for
@return: a vector of the files with the specified extension
*/
std::vector<std::string> utils::get_files(const std::string& dir, const std::string& ext)
{
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(dir))
    {
        if (entry.path().extension() == ext)
        {
            files.push_back(entry.path().string());
        }
    }
    return files;
}

/*
filter out characters from a string

@param str: the string to filter
@param chars: the characters to filter out
@return: the filtered string
*/
std::string utils::filter(const std::string& str, const std::string& chars)
{
	std::string s = str;
	s.erase(std::remove_if(s.begin(), s.end(), [&chars](char c)
		{ return chars.find(c) != std::string::npos; }),
		s.end());
	return s;
}

/*
filter out characters from a string, leaving only the digits

@param str: the string to filter
@return: the digits from the string
*/
std::string utils::digits(const std::string& str) {
	return filter(str, "0123456789");
}


/*
filter out the digits and punctuation from a string, leaving only the letters

@param str: the string to filter
@return: the letters from the string
*/
std::string utils::letters(const std::string& str) {
	return filter(str, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
}