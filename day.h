#ifndef ADVENT2023_DAY_H
#define ADVENT2023_DAY_H

#include <string>

// Day is an abstract class that defines the interface for all days
class Day {
public:
	virtual std::string run() = 0;
};

#endif // ADVENT2023_DAY_H