#include <sys/stat.h>
#include <cerrno>
#include <new>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "logger.h"

namespace id {

Logger* Logger::instance = nullptr;

Logger* Logger::getInstance()
{
	static Logger instance;
	int error_mkdir = std::system("mkdir logs -p");
	(void)error_mkdir;
	
	return &instance;

}

Logger::Logger()
: logLevel(L_INFO), logPath("./logs/"), logFile("DEBUG_LOG_"), logString("")
{
	#ifndef _DEBUG
	logFile = "RELEASE_LOG";
	#endif
	setLogFile();
}

auto Logger::getTime() -> std::string
{
	time_t t = time(0);
	struct tm* now = localtime(&t);	
	std::string sTime; 
	sTime += std::to_string(now->tm_hour);
	sTime += ":";
	sTime += std::to_string(now->tm_min);
	sTime += ":";
	sTime += std::to_string(now->tm_sec);
	sTime += " ";
	return sTime;
}
auto Logger::setLogFile() ->void
{

	time_t t = time(0);
	struct tm* now = localtime(&t);

	logFile += std::to_string((now->tm_year + 1900));
	logFile += "-";
	logFile += std::to_string((now->tm_mon + 1));
	logFile += "-";
	logFile += std::to_string(now->tm_mday);
	logFile += "_";
	logFile += std::to_string(now->tm_hour);
	logFile += ":";
	logFile += std::to_string(now->tm_min);
	logFile += ":";
	logFile += std::to_string(now->tm_sec);
	logFile += ".txt";

	std::ofstream logOFS((logPath + logFile).c_str(), std::ios_base::out | std::ios_base::app);

	logOFS << logFile << std::endl << std::endl;

	logOFS.close();
}

auto Logger::recordLogFlag(LG_LEVEL logFlag) -> std::string
{
	switch (logFlag)
	{
		case L_DEBUG:
			return "DEBUG   ->";
		break;

		case L_ERROR:
			return "ERROR   ->";
		break;

		case L_WARNING:
			return "WARNING ->";
		break;

		case L_INFO:
			return "INFO    ->";
		break;

		case L_GAME:
			return "GAME    ->";
		break;

		case L_LOOP:
			return "LOOP	->";
		break;
	
		default:
			return "";
			break;
	}
}



}// end id

