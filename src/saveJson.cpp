#include <iostream>
#include "txtLogger.h"
#include "saveJson.h"

int id::json::JsonValue::indentation = 0;

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();

	auto indent() -> void
	{
		for (int i = 0; i < id::json::JsonValue::indentation; ++i)
			std::cout << "\t";
	}

}

namespace id {
namespace json {

JsonObject::JsonObject()
{
	logger->log("Creating JsonObject...", LL_DEBUG);

	logger->log("JsonObject has been created.");
}

JsonObject::JsonObject(JsonObject const& obj)
{
	logger->log("Creating JsonObject by copy...", LL_DEBUG);
	
	mapValue = obj.getMapValue();

	logger->log("JsonObject has been created by copy.");
}

JsonObject::~JsonObject()
{
	logger->log("Deleting JsonObject...", LL_DEBUG);

	logger->log("JsonObject has been deleted.");
}

auto JsonObject::addInObject(std::string str, JsonValue* val) -> void
{
	mapValue[str] = val;
}

auto JsonObject::serialize() -> void
{
	std::cout << "{" << std::endl;
	if (!mapValue.empty())
	{

		indentation++;

		unsigned int i = 1;
		unsigned int j = mapValue.size();
		for (auto&& val : mapValue)
		{
			indent();
			std::cout << "\"" << val.first << "\" : ";
			val.second->serialize();
			if ( i == j)
				std::cout << std::endl;
			else
				std::cout << "," << std::endl;
			++i;
		}

		--indentation;
		indent();
	}
	std::cout << "}";
}

JsonArray::JsonArray()
{
	logger->log("Creating JsonArray...", LL_DEBUG);

	logger->log("JsonArray has been created.");
}

JsonArray::JsonArray(JsonArray const& arr)
{
	logger->log("Creating JsonArray by copy...", LL_DEBUG);
	
	arrayValue = arr.getArrayValue();

	logger->log("JsonArray has been created by copy.");
}

JsonArray::~JsonArray()
{
	logger->log("Deleting JsonArray...", LL_DEBUG);

	logger->log("JsonArray has been deleted.");
}

auto JsonArray::addInArray(JsonValue* val) -> void
{
	arrayValue.push_back(val);
}

auto JsonArray::serialize() -> void
{
	std::cout << "[ ";

	unsigned int i = 1;
	unsigned int j = arrayValue.size();
	for (auto&& val : arrayValue)
	{
		val->serialize();
		if (i != j)
			std::cout << ", ";
		++i;
	}
	std::cout << "]";
}


JsonString::JsonString(std::string str)
:str(str)
{
	logger->log("Creating JsonString...", LL_DEBUG);

	logger->log("JsonString has been created.");
}

JsonString::~JsonString()
{
	logger->log("Deleting JsonString...", LL_DEBUG);

	logger->log("JsonString has been deleted.");
}

auto JsonString::serialize() -> void
{
	std::cout << "\"" << str << "\"";

}



JsonBool::JsonBool(bool boolean)
:boolean(boolean)
{
	logger->log("Creating JsonBool...", LL_DEBUG);

	logger->log("JsonBool has been created.");
}

JsonBool::~JsonBool()
{
	logger->log("Deleting JsonBool...", LL_DEBUG);

	logger->log("JsonBool has been deleted.");
}

auto JsonBool::serialize() -> void
{
	if (boolean)
		std::cout << "true";
	else
		std::cout << "false";

}


JsonNumber::JsonNumber(long double number)
:number(number)
{
	logger->log("Creating JsonNumber...", LL_DEBUG);

	logger->log("JsonNumber has been created.");
}

JsonNumber::~JsonNumber()
{
	logger->log("Deleting JsonNumber...", LL_DEBUG);

	logger->log("JsonNumber has been deleted.");
}

auto JsonNumber::serialize() -> void
{
	std::cout << number;
}




JsonNull::JsonNull()
{
	logger->log("Creating JsonNull...", LL_DEBUG);

}

JsonNull::~JsonNull()
{
	logger->log("Deleting JsonNull...", LL_DEBUG);

	logger->log("JsonNull has been deleted.");
}

auto JsonNull::serialize() -> void
{
	std::cout << "null";
}


} // namespace json 
} // namespace id
