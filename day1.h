#ifndef ADVENT2023_DAY_1_H
#define ADVENT2023_DAY_1_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <map>

#include "utils.h"
#include "day.h"

class Day1 : public Day {
private:
	std::string path;
	std::map<std::string, std::string> digits{
		{"one", "1"},
		{"two", "2"},
		{"three", "3"},
		{"four", "4"},
		{"five", "5"},
		{"six", "6"},
		{"seven", "7"},
		{"eight", "8"},
		{"nine", "9"},
		{"zero", "0"}
	};

public:
	Day1(std::string path) : path(path) {}

	std::string run() override
	{
		std::string part1 = this->part1();
		std::string part2 = this->part2();
		return utils::join({ part1, part2 }, '\n');
	}

	std::string part1()
	{
		std::ifstream file(path);
		if (!file.is_open())
			return "ERROR: file not found";

		// iterate through each line of the file
		std::vector<int> values;
		std::string line;
		while (std::getline(file, line)) {
			// get the first digit character and the last digit character, then add those to the values vector
			std::string first = line.substr(line.find_first_of("1234567890"), 1);
			std::string last = line.substr(line.find_last_of("1234567890"), 1);
			values.push_back(std::stoi(first + last));
		}

		file.close();

		// sum up the values vector and return the result
		return "\tPart 1: " + std::to_string(
			std::accumulate(
				values.begin(),
				values.end(),
				0,
				std::plus<int>()
			)
		);
	}

	std::string part2()
	{
		std::ifstream file(path);
		if (!file.is_open())
			return "ERROR: file not found";

		// iterate through each line of the file
		std::vector<int> values;
		std::string line;
		while (std::getline(file, line)) {
			std::string str = "";
			// go forwards through line
			for (int i = 0; i < line.length(); ++i) {
				// check if current character is a digit
				if (isdigit(line[i])) {
					str += line[i];
					break;
				}
				// check if current character is start of a key in nums
				bool found = false;
				for (auto& [key, value] : digits) {
					if (line.substr(i, key.length()) == key) {
						str += value;
						found = true;
						break;
					}
				}
				if (found)
					break;
			}

			// go backwards through line
			for (int i = line.length(); i >= 0; --i) {
				// check if current character is a digit
				if (isdigit(line[i])) {
					str += line[i];
					break;
				}
				// check if current character is start of a key in nums
				bool found = false;
				for (auto& [key, value] : digits) {
					if (line.substr(i, key.length()) == key) {
						str += value;
						found = true;
						break;
					}
				}
				if (found)
					break;
			}
			if (str.length() < 2) {
				return "Bad read";
			}
			int num = std::stoi(str);
			values.push_back(num);
		}

		file.close();

		// sum up the values vector and return the result
		return "\tPart 2: " + std::to_string(
			std::accumulate(
				values.begin(),
				values.end(),
				0,
				std::plus<int>()
			)
		);
	}
};

#endif // ADVENT2023_DAY_1_H