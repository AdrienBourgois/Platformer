#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#define xstr(s) string(s)
#define string(s) #s

#define LOG(LVL, ...) id::Logger::getInstance()->logT(LVL, __FILE__ ":" xstr(__LINE__) " in", __FUNCTION__,__VA_ARGS__)

#include <fstream>
#include <string>
#include <cstdarg>
#include <iostream>
#include <sstream>
#include <vector>
enum LG_LEVEL
{
	L_ERROR = 0,
	L_WARNING,
	L_INFO,
	L_GAME,
	L_DEBUG,
	L_LOOP,
	L_COUNT
	
};
namespace id {

class Logger
{
public:
	static Logger* getInstance();

	~Logger() = default;

	Logger(Logger const&) = delete;
	Logger& operator=(Logger const&) = delete;
	
	auto getTime() -> std::string;
	auto getLogLevel() const -> LG_LEVEL { return logLevel;}
	auto getBufLogString() -> std::vector<std::string>& {return bufLogString;}
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
	std::vector<std::string>	bufLogString;
	auto setLogFile() -> void;
	
	auto recordLogFlag(LG_LEVEL) -> std::string;
};
#include "logger.inl"

}//end id

#endif
