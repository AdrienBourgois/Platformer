#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#ifndef _DEBUG

#define xstr(s) string(s)
#define string(s) #s

#define LOG(...) id::Logger::getInstance()->logT(__FILE__ ":" xstr(__LINE__) " in function", __FUNCTION__,__VA_ARGS__)
#else
#define LOG(...)
#endif

#include <fstream>
#include <string>
#include <cstdarg>
#include <iostream>
#include <sstream>

namespace id {


enum LOG_LEVEL
{
	_ERROR = 0,
	_WARNING,
	_INFO,
	_GAME,
	_DEBUG,
	_ALL
};

class Logger
{
public:
	static Logger* getInstance();

	~Logger() = default;

	Logger(Logger const&) = delete;
	Logger& operator=(Logger const&) = delete;

	auto getLogLevel() const -> LOG_LEVEL { return logLevel;}
	auto setLog(LOG_LEVEL loglvl) -> void { logLevel = loglvl;}

	template<typename ... Param>
	void logT();

	template<typename T, typename ... param>
	void logT(const T first, const param... others);

	static Logger* instance;
private:
	Logger();
	LOG_LEVEL	logLevel;
		
	std::string	logPath;
	std::string	logFile;
	std::stringstream	logString;
	auto setLogFile() -> void;
	
	auto recordLogFlag(std::ofstream&, LOG_LEVEL) -> void;
};
#include "logger.inl"

}//end id

#endif
