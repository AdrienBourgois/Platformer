#include "logger.h"

template<typename T, typename ... Param>
void Logger::logT(LG_LEVEL logLevel, T value)
{
	std::stringstream ss;
	ss << getTime();
	ss << recordLogFlag(logLevel);
	ss << logString.str();
	ss << value << '\n' ;
	std::ofstream logOF ((logPath + logFile).c_str(), std::ios_base::out | std::ios_base::app);

	#ifndef _DEBUG
	logOF << ss.str() << std::endl;
	#else
	if(logLevel != L_WARNING || L_ERROR)
		logOF << ss.str() << std::endl;
	#endif
	logOF.close();

	bufLogString.push_back(ss.str());

	(void)logLevel;
	#ifdef _DEBUG
//		std::cout << ss.str() << std::endl;
	#else
//		std::cout << ss.str() << std::endl;
	#endif
	
	logString.str("");
}

template<typename T, typename ... param>
void Logger::logT(LG_LEVEL logLevel,T const value ,const param... others)
{
	logString << value <<" ";
	logT(logLevel, others...);
}

