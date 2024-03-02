#ifndef ADVENT2023_DAY_3_H
#define ADVENT2023_DAY_3_H

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <set>

#include "utils.h"
#include "debug.h"
#include "day.h"

class Number {
public:
	Number(int value, int length, std::pair<int, int> startPos, std::pair<int, int> endPos) : value(value), length(length), startPos(startPos), endPos(endPos) {}
	Number(int value, int length, std::pair<int, int> startPos) : value(value), length(length), startPos(startPos) {
		endPos = std::make_pair(startPos.first + length - 1, startPos.second);
	}
	int value;
	int length;
	std::pair<int, int> startPos;
	std::pair<int, int> endPos;

	std::vector<std::pair<int, int>> getPositions() {
		std::vector<std::pair<int, int>> positions;
		if (startPos.first == endPos.first) {
			for (int i = startPos.second; i <= endPos.second; i++) {
				positions.push_back(std::make_pair(startPos.first, i));
			}
		}
		else if (startPos.second == endPos.second) {
			for (int i = startPos.first; i <= endPos.first; i++) {
				positions.push_back(std::make_pair(i, startPos.second));
			}
		}
		return positions;
	}

	bool contains(std::pair<int, int> pos) {
		std::vector<std::pair<int, int>> positions = getPositions();
		return std::find(positions.begin(), positions.end(), pos) != positions.end();
	}

	std::vector<std::pair<int, int>> getSurroundingPositions() {
		std::vector<std::pair<int, int>> positions = getPositions();
		std::vector<std::pair<int, int>> surroundingPositions;
		for (std::pair<int, int> pos : positions) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (i == 0 && j == 0) {
						continue;
					}
					std::pair<int, int> newPos = std::make_pair(pos.first + i, pos.second + j);
					if (std::find(surroundingPositions.begin(), surroundingPositions.end(), newPos) == surroundingPositions.end() && !contains(newPos)) {
						surroundingPositions.push_back(newPos);
					}
				}
			}
		}
		return surroundingPositions;
	}

	std::string toString() {
		return "Number: " + std::to_string(value) + " Length: " + std::to_string(length)
			+ " StartPos: (" + std::to_string(startPos.first) + ", " + std::to_string(startPos.second)
			+ ") EndPos: (" + std::to_string(endPos.first) + ", " + std::to_string(endPos.second) + ")";
	}
};

class Symbol {
private:
	std::pair<int, int> pos;
	char value;
public:
	Symbol(std::pair<int, int> pos, char value) : pos(pos), value(value) {}

	std::pair<int, int> getPos() {
		return pos;
	}

	char getValue() {
		return value;
	}

	std::vector<std::pair<int,int>> getSurroundingPositions() {
		std::vector<std::pair<int, int>> surroundingPositions;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (i == 0 && j == 0) {
					continue;
				}
				std::pair<int, int> newPos = std::make_pair(pos.first + i, pos.second + j);
				surroundingPositions.push_back(newPos);
			}
		}
		return surroundingPositions;
	}
};

class Grid {
private:
	debug::Debug debugger;
	std::vector<Number> numbers;
	std::vector<Symbol> symbols;
	int width;
	int height;

public:
	Grid(std::string fname) {
		debugger.setName("Grid");
		debugger.info("Reading file: " + fname);

		std::ifstream file(fname);
		if (!file.is_open()) {
			debugger.error("Could not open file: " + fname);
			throw std::runtime_error("Could not open file");
		}

		std::string line;
		std::getline(file, line);
		width = line.length();
		debugger.info("Width: " + std::to_string(width));
		
		// iterate through the file
		int y = 0;
		do {
			for (int x = 0; x < line.length(); x++) {
				
				// populate squares vector with the grid
				char value = line[x];
				
				// if the value is a number, add it to the numbers vector
				if (std::isdigit(value)) {
					
					int v = value - '0';
					int length = 1;
					std::pair<int, int> startPos = std::make_pair(x, y);
					while (x + length < line.length() && std::isdigit(line[x + length])) {
						int nextDigit = line[x + length] - '0';
						v = (v * 10) + nextDigit;
						length++;
					}
					
					Number n(v, length, startPos);
					numbers.push_back(n);
					x += length - 1;
				}

				if (!std::isdigit(value) && value != '.') {
					Symbol s(std::make_pair(x, y), value);
					symbols.push_back(s);
				}
			}
			y++;
		} while (std::getline(file, line));

		height = y / width;
		debugger.info("Height: " + std::to_string(height));
		debugger.info("Numbers length: " + std::to_string(numbers.size()));
		debugger.info("Symbols length: " + std::to_string(symbols.size()));

		file.close();
	}

	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

	std::vector<Number> getNumbers() {
		return numbers;
	}

	std::vector<Symbol> getSymbols() {
		return symbols;
	}

	bool isNumber(std::pair<int, int> pos) {
		return std::find_if(numbers.begin(), numbers.end(), [pos](Number n) { return n.contains(pos); }) != numbers.end();
	}

	bool isNumber(int x, int y) {
		return isNumber(std::make_pair(x, y));
	}
};


class Day3 : public Day {
	std::string path;
public:
	Day3(std::string path) : path(std::move(path)) {}

	std::string run() override {
		std::string p1 = part1();
		std::string p2 = part2();
		return utils::join({p1, p2}, '\n');
	}

	std::string part1() {
		debug::Debug debugger("Day3", false);
		Grid grid(path);

		// get the numbers vector and the symbols vector
		std::vector<Number> numbers = grid.getNumbers();
		std::vector<Symbol> symbols = grid.getSymbols();

		int sum = std::accumulate(numbers.begin(), numbers.end(), 0, [](int acc, Number n) { return acc + n.value; });
		
		debugger.info("Numbers length: " + std::to_string(numbers.size()));
		debugger.info("Symbols length: " + std::to_string(symbols.size()));

		// iterate through the symbols vector and filter out any numbers in the numbers vector that are next to the symbol
		for (Symbol s : symbols) {
			std::vector<std::pair<int, int>> surroundingPositions = s.getSurroundingPositions();
			numbers.erase(std::remove_if(numbers.begin(), numbers.end(), [surroundingPositions](Number n) {
				for (std::pair<int, int> pos : surroundingPositions) {
					if (n.contains(pos)) {
						return true;
					}
				}
				return false;
			}), numbers.end());
		}

		debugger.info("Numbers length after filtering: " + std::to_string(numbers.size()));
		
		for (Number n : numbers) {
			sum -= n.value;
		}

		return "\tPart 1: " + std::to_string(sum);

	}

	std::string part2() {
		debug::Debug debugger("Day3", true);
		Grid grid(path);
		
		std::vector<Number> numbers = grid.getNumbers();
		std::vector<Symbol> symbols = grid.getSymbols();

		unsigned long long sum = 0;

		for (Symbol s : symbols) {
			// if the symbol is a '*', then we need to make sure it is next to 2 numbers
			if (s.getValue() == '*') {
				std::vector<std::pair<int, int>> surroundingPositions = s.getSurroundingPositions();
				std::vector<Number> surroundingNumbers;
				for (Number n : numbers) {
					for (std::pair<int, int> pos : surroundingPositions) {
						if (n.contains(pos)) {
							surroundingNumbers.push_back(n);
							break;
						}
					}
				}
				if (surroundingNumbers.size() < 2) {
					continue;
				}

				if (surroundingNumbers.size() > 2) {
					debugger.warn("More than 2 numbers next to a '*'");
					for (Number n : surroundingNumbers) {
						std::cout << n.value << ' ';
					}
					std::cout << std::endl;
				}

				unsigned long long product = std::accumulate(surroundingNumbers.begin(), surroundingNumbers.end(), 1, [](unsigned long long acc, Number n) { return acc * n.value; });
				sum += product;
			}
		}

		return "\tPart 2: " + std::to_string(sum);
	}

};

#endif //ADVENT2023_DAY_3_H