#include <sys/stat.h>
#include <cerrno>
#include <new>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "txtLogger.h"

namespace id {

TXTLogger* TXTLogger::instance = nullptr;

TXTLogger* TXTLogger::getInstance()
{
	static TXTLogger instance;

	int error_mkdir = std::system("mkdir logs -p");
	(void)error_mkdir;

	return &instance;
}

TXTLogger::TXTLogger()
: logLevel(LL_INFO), logPath("./logs/"), logFile("LOG_")
{
	setLogFile();
}

void TXTLogger::log(std::string& text, E_LOG_FLAG logFlag)
{
	if (logLevel == LL_DEBUG && logFlag == LL_GAME)
		return;

	if (logFlag <= logLevel)
	{
		std::ofstream logOFS((logPath + logFile).c_str(), std::ios_base::out | std::ios_base::app);

		if (logOFS.fail())
		{
			std::cout << "WARNING -> Could not open logFile." << std::endl;
		}

		recordLogFlag(logOFS, logFlag);

		logOFS << text << std::endl;

		logOFS.close();
	}
}

void TXTLogger::log(std::string& text, void* ptr, E_LOG_FLAG logFlag)
{
	if (logLevel == LL_DEBUG && logFlag == LL_GAME)
		return;

	if (logFlag <= logLevel)
	{
		std::ofstream logOFS((logPath + logFile).c_str(), std::ios_base::out | std::ios_base::app);

		if (logOFS.fail())
		{
			std::cout << "WARNING -> Could not open logFile." << std::endl;
			return;
		}

		recordLogFlag(logOFS, logFlag);

		logOFS << text << ptr << std::endl;

		logOFS.close();
	}
}

void TXTLogger::log(char const* text, E_LOG_FLAG logFlag)
{
	if (logLevel == LL_DEBUG && logFlag == LL_GAME)
		return;

	if (logFlag <= logLevel)
	{
		std::ofstream logOFS((logPath + logFile).c_str(), std::ios_base::out | std::ios_base::app);

		if (logOFS.fail())
		{
			std::cout << "WARNING -> Could not open logFile." << std::endl;
		}

		recordLogFlag(logOFS, logFlag);

		logOFS << text << std::endl;

		logOFS.close();
	}
}

void TXTLogger::log(char const* text, void* ptr, E_LOG_FLAG logFlag)
{
	if (logLevel == LL_DEBUG && logFlag == LL_GAME)
		return;

	if (logFlag <= logLevel)
	{
		std::ofstream logOFS((logPath + logFile).c_str(), std::ios_base::out | std::ios_base::app);

		if (logOFS.fail())
		{
			std::cout << "WARNING -> Could not open logFile." << std::endl;
			return;
		}

		recordLogFlag(logOFS, logFlag);

		logOFS << text << ptr << std::endl;

		logOFS.close();
	}
}

void TXTLogger::recordLogFlag(std::ofstream& logOFS, E_LOG_FLAG logFlag)
{
	switch (logFlag)
	{
		case LL_DEBUG:
			logOFS << "DEBUG   -> ";
		break;

		case LL_ERROR:
			logOFS << "ERROR   -> ";
		break;

		case LL_WARNING:
			logOFS << "WARNING -> ";
		break;

		case LL_INFO:
			logOFS << "INFO    -> ";
		break;

		case LL_GAME:
			logOFS << "GAME    -> ";
		break;

		default:
			break;
	}
}

void TXTLogger::setLogFile()
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

} //end namespace id
