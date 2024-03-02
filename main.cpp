#include <iostream>

#include "utils.h"
#include "day1.h"
#include "day2.h"
#include "day3.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "ERROR: no input directory specified" << std::endl;
		return 1;
	}

	// get list of text files in directory
	std::string dir = argv[1];
	std::cout << "Scanning directory " << dir << "..." << std::endl;
	std::vector<std::string> files = utils::get_files(dir, ".txt");

	// find appropriate class based on file name, run day and print results
	for (std::string file : files)
	{
		std::cout << "\nWorking on file " << file << "..." << std::endl;
		std::string day = utils::split(file, '\\').back();
		day = utils::split(day, '.')[0];
		std::cout << day << ":" << std::endl;

		if (day == "day1")
		{
			Day1 d(file);
			std::cout << d.run() << std::endl;
		}
		else if (day == "day2")
		{
			Day2 d(file);
			std::cout << d.run() << std::endl;
		}
		else if (day == "day3")
		{
			Day3 d(file);
			std::cout << d.run() << std::endl;
		}
		else
		{
			std::cout << "ERROR: invalid day" << std::endl;
			return 1;
		}
	}

	return 0;
}