#include "logger.h"
template<typename T, typename ... Param>
void Logger::logT(LG_LEVEL logLevel, T value)
{
	std::stringstream ss;
	ss << recordLogFlag(logLevel);
	ss << logString.str();
	ss << value;

	(void)logLevel;
	
	std::cout << ss.str() << std::endl;
//	addBufferString("%s", logString);
	logString.str("");
}

template<typename T, typename ... param>
void Logger::logT(LG_LEVEL logLevel,T const value ,const param... others)
{
	logString << value <<" ";
	logT(logLevel, others...);
}

