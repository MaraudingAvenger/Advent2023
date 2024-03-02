#ifndef ADVENT2023_DAY_2_H
#define ADVENT2023_DAY_2_H

#include <string>
#include <vector>
#include <fstream>
#include <map>

#include "day.h"
#include "utils.h"

class Day2 : public Day {
private:
	bool part_one_done = false;
	std::string path;
	std::map<int, std::map<std::string, int>> scores;

public:
	Day2(std::string path) : path(std::move(path)) {}

	std::string run() override {
		std::string part1 = this->part1();
		std::string part2 = this->part2();
		return utils::join({ part1, part2 }, "\n");
	}

	std::string part1() {
		std::ifstream file(path);
		if (!file.is_open())
			return "ERROR: file not found";

		// "Game 1: 1 red, 3 blue, 11 green; 1 blue, 5 red; ..."
		std::string line;
		while (std::getline(file, line)) {
			// "Game 123: ..."
			//      ^---^
			int game = std::stoi(line.substr(5, line.find(':') - 5));

			scores[game] = std::map<std::string, int>{
				{"red", 0},
				{"blue", 0},
				{"green", 0}
			};

			// "Game 1: 1 red, 3 blue, 11 green; 1 blue, 5 red; ..."
			//          ^------------------------------------------^
			std::string show_string = utils::split(line, ": ")[1];

			// "1 red, 3 blue, 11 green; 1 blue, 5 red; ..."
			// ^-----------------------^
			std::vector<std::string> shows = utils::split(show_string, "; ");

			for (const std::string& show : shows) {
				// "1 red, 3 blue, 11 green"
				// ^-----^
				std::vector<std::string> colors = utils::split(show, ", ");
				for (const std::string& color : colors) {
					// "1 red"
					// ^-^
					int amount = std::stoi(color.substr(0, color.find(' ')));

					// "1 red"
					//    ^--^
					std::string color_name = color.substr(color.find(' ') + 1);
					scores[game][color_name] = std::max(scores[game][color_name], amount);
				}
			}

		} // while (std::getline(file, line))

		std::map<std::string, int> check{
			{"red", 12},
			{"blue", 14},
			{"green", 13}
		};

		// iterate over all games, find out which ones were possible
		// with the number of stones in check
		int id_sum = 0;
		for (const auto& [game, score] : scores) {
			bool possible = true;
			for (const auto& [color, amount] : score) {
				if (check[color] < amount) {
					possible = false;
					break;
				}
			}
			if (possible)
				id_sum += game;
		}

		part_one_done = true;
		return "\tPart 1: " + std::to_string(id_sum);
	}

	std::string part2() {
		if (!part_one_done)
			this->part1();

		unsigned int stone_score = 0;

		// iterate over scorres, find minimum number of stones needed of each color
		for (const auto& [game, score] : scores) {

			unsigned int game_score = 1;
			for (const auto& [color, amount] : score) {
				game_score *= amount;
			}
			stone_score += game_score;
		}

		return "\tPart 2: " + std::to_string(stone_score);
	}
};

#endif // ADVENT2023_DAY_2_H