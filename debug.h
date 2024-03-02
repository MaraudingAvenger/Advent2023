#ifndef _ADVENT2023_DEBUG_H_
#define _ADVENT2023_DEBUG_H_

#include <fstream>
#include <string>

namespace debug {
	class Debug {
	private:
		std::string _name;
		bool _enabled;
	public:
		Debug() : _name(""), _enabled(false) {}
		Debug(const std::string& name) : _name(name), _enabled(false) {}
		Debug(const std::string& name, bool enabled) : _name(name), _enabled(enabled) {}

		void setName(const std::string& name) { _name = name; }
		void enable() { _enabled = true; }
		void disable() { _enabled = false; }
		bool isEnabled() { return _enabled; }

		void log(const std::string& message);
		void warn(const std::string& message);
		void error(const std::string& message);
		void info(const std::string& message);
	};
}

#endif // _ADVENT2023_DEBUG_H_