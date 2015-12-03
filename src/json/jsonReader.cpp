#include <sstream>
#include "txtLogger.h"
#include "json/jsonValue.h"
#include "json/jsonReader.h"
#include "fileUtility.h"

#include <iostream>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

JsonReader::JsonReader(std::string name)
:file(("./assets/json/" + name + ".json").c_str(), std::ios_base::in)
{
	std::string str = "Creating jsonReader to read ./assets/json/" + name + ".json...";
	logger->log(str, LL_DEBUG);

	logger->log("Jsonreader has been created.");
}

JsonReader::~JsonReader()
{
	logger->log("Deleting JsonReader...", LL_DEBUG);

	file.close();

	logger->log("JsonReader has been deleted.");
}

auto JsonReader::readBool(std::string key) -> bool
{
	file.seekg(0, file.beg);
	std::string line;
	std::string keyFile;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					if ( id::FileUtility::getStringWithoutExtra(keyFile) == "true" )
						return true;
					else 
						return false;
				}
			}
		}
	}
	return false;
}

auto JsonReader::readString(std::string key) -> std::string
{
	file.seekg(0, file.beg);
	std::string line;
	std::string keyFile;
	std::string finalstr = "";
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					finalstr = id::FileUtility::getStringWithoutExtra(keyFile); 
					return finalstr;
				}
			}
		}
	}
	return finalstr;

}

auto JsonReader::readNull(std::string key) -> bool
{
	file.seekg(0, file.beg);
	std::string line;
	std::string keyFile;
	std::string finalstr;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					finalstr = id::FileUtility::getStringWithoutExtra(keyFile); 
					if (finalstr == "null")
						return true;
					else 
						return false;
				}
			}
		}
	}
	return false;



}

auto JsonReader::readNumber(std::string key) -> double
{
	file.seekg(0, file.beg);
	std::string line;
	std::string keyFile;
	std::string finalNumber;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					finalNumber = id::FileUtility::getNumberStringFromString(keyFile);
					return std::stod(finalNumber);
				}
			}
		}
	}
	return 0;
}

auto JsonReader::readStringArray(std::string key) -> std::vector<std::string>
{
	file.seekg(0, file.beg);
	std::string line;
	std::string keyFile;
	std::string finalstr;
	std::vector<std::string> vecVal;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile; // ignore '['
					sstr >> keyFile;
					while (keyFile != "]")
					{
						finalstr = id::FileUtility::getStringWithoutExtra(keyFile);
						vecVal.push_back(finalstr);
						sstr >> keyFile;
					}
				}
			}
		}
	}
	return vecVal;
}

auto JsonReader::readBoolArray(std::string key) -> std::vector<bool>
{
	file.seekg(0, file.beg);
	std::string line;
	std::string keyFile;
	std::string finalstr;
	std::vector<bool> vecVal;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile; // ignore '['
					sstr >> keyFile;
					while (keyFile != "]")
					{
						finalstr = id::FileUtility::getStringWithoutExtra(keyFile);
						if (finalstr == "true")
							vecVal.push_back(true);
						else
							vecVal.push_back(false);
						sstr >> keyFile;
					}
				}
			}
		}
	}
	return vecVal;
}

auto JsonReader::readNumberArray(std::string key) -> std::vector<double>
{
	file.seekg(0, file.beg);
	std::string line;
	std::string keyFile;
	std::string finalNumber;
	std::vector<double> vecVal;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile; // ignore '['
					sstr >> keyFile;
					while (keyFile != "]")
					{
						finalNumber = id::FileUtility::getNumberStringFromString(keyFile);
						vecVal.push_back(std::stod(finalNumber));
						sstr >> keyFile;
					}
				}
			}
		}
	}
	return vecVal;
}



} // namespace json
} // namespace id
