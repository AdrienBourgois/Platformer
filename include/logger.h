#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#ifndef _DEBUG

#define xstr(s) string(s)
#define string(s) #s

#define LOG(LVL, ...) id::Logger::getInstance()->logT(LVL, __FILE__ ":" xstr(__LINE__) " in function", __FUNCTION__,__VA_ARGS__)
#else
#define LOG(...)
#endif

#include <fstream>
#include <string>
#include <cstdarg>
#include <iostream>
#include <sstream>
enum LG_LEVEL
{
	_ERROR = 0,
	_WARNING,
	_INFO,
	_GAME,
	_DEBUG,
	_ALL
};
namespace id {

class Logger
{
public:
	static Logger* getInstance();

	~Logger() = default;

	Logger(Logger const&) = delete;
	Logger& operator=(Logger const&) = delete;

	auto getLogLevel() const -> LG_LEVEL { return logLevel;}
	auto setLog(LG_LEVEL loglvl) -> void { logLevel = loglvl;}

	template<typename T,typename ... Param>
	void logT(LG_LEVEL, T value);

	template<typename T, typename ... param>
	void logT(const LG_LEVEL, T const value,const param... others);

	static Logger* instance;
private:
	Logger();
	LG_LEVEL	logLevel;
		
	std::string	logPath;
	std::string	logFile;
	std::stringstream	logString;
	auto setLogFile() -> void;
	
	auto recordLogFlag(LG_LEVEL) -> std::string;
};
#include "logger.inl"

}//end id

#endif
