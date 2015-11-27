#include "logger.h"
template<typename ... Param>
void Logger::logT()
{
	std::cout << logString.str() << std::endl;
//	addBufferString("%s", logString);
	logString.str("");
}

template<typename T, typename ... param>
void Logger::logT(const T first, const param... others)
{
	logString << first << " ";
	logT(others...);
}


