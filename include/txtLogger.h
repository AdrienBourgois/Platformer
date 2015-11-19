#ifndef TXT_LOGGER_H_INCLUDED
#define TXT_LOGGER_H_INCLUDED

#include <fstream>
#include <string>

namespace id {

enum E_LOG_FLAG
{
	LL_ERROR = 0,
	LL_WARNING,
	LL_INFO,
	LL_GAME,
	LL_DEBUG,
	LL_ALL
};

class TXTLogger
{
  public:
	static TXTLogger* getInstance();

	~TXTLogger() = default;
	TXTLogger(TXTLogger const&) = delete;
	TXTLogger& operator=(TXTLogger const&) = delete;

	auto getLogLevel() const -> E_LOG_FLAG { return logLevel; }
	void setLogLevel(E_LOG_FLAG logFlag) { logLevel = logFlag; }

	void log(std::string&, E_LOG_FLAG = LL_INFO);
	void log(std::string&, void*, E_LOG_FLAG = LL_INFO);

	void log(char const*, E_LOG_FLAG = LL_INFO);
	void log(char const*, void*, E_LOG_FLAG = LL_INFO);

	static TXTLogger* instance;

  private:
	TXTLogger();

	E_LOG_FLAG logLevel;

	std::string logPath;
	std::string logFile;
	void setLogFile();

	void recordLogFlag(std::ofstream&, E_LOG_FLAG);
};


} //end namespace id

#endif //TXT_LOGGER_H_INCLUDED
