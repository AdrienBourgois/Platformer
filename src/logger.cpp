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
: logLevel(_INFO), logPath("./logs/"), logFile("DEBUG_LOG_"), logString("")
{
	setLogFile();
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

void Logger::recordLogFlag(std::ofstream& logOFS, LOG_LEVEL logFlag)
{
	switch (logFlag)
	{
		case _DEBUG:
			logOFS << "DEBUG   -> ";
		break;

		case _ERROR:
			logOFS << "ERROR   -> ";
		break;

		case _WARNING:
			logOFS << "WARNING -> ";
		break;

		case _INFO:
			logOFS << "INFO    -> ";
		break;

		case _GAME:
			logOFS << "GAME    -> ";
		break;

		default:
			break;
	}
}



}// end id

