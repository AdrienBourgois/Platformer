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

JsonObject::~JsonObject()
{
	logger->log("Deleting JsonObject...", LL_DEBUG);

	logger->log("JsonObject has been deleted.");
}

auto JsonObject::serialize() -> void
{
	indent();
	std::cout << "{" << std::endl;
	if (mapValue.empty())
	{
		std::cout << "}" << std::endl;
		return;
	}

	indentation++;

	for (auto&& val : mapValue)
	{
		indent();
		std::cout << "\"" << val.first << "\" :";
		val.second->serialize();
	}

	--indentation;
	indent();
	std::cout << "}" << std::endl;
}

auto JsonObject::operator[](std::string str) -> JsonValue*&
{
	return mapValue[str];
}

auto JsonObject::serialize(std::ostream& os) -> void
{
(void)os;
}

JsonArray::JsonArray()
{
	logger->log("Creating JsonArray...", LL_DEBUG);

	logger->log("JsonArray has been created.");
}

JsonArray::~JsonArray()
{
	logger->log("Deleting JsonArray...", LL_DEBUG);

	logger->log("JsonArray has been deleted.");
}

auto JsonArray::serialize() -> void
{

}

auto JsonArray::serialize(std::ostream& os) -> void
{

(void)os;
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
}

auto JsonString::serialize(std::ostream& os) -> void
{
(void)os;

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

}

auto JsonBool::serialize(std::ostream& os) -> void
{
(void)os;

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
	indent();
	std::cout << number << "," << std::endl;
}

auto JsonNumber::serialize(std::ostream& os) -> void
{
(void)os;

}


JsonNull::JsonNull()
{
	logger->log("Creating JsonNull...", LL_DEBUG);

	logger->log("JsonNull has been created.");
}

JsonNull::~JsonNull()
{
	logger->log("Deleting JsonNull...", LL_DEBUG);

	logger->log("JsonNull has been deleted.");
}

auto JsonNull::serialize() -> void
{

}

auto JsonNull::serialize(std::ostream& os) -> void
{
(void)os;

}

} // namespace json 
} // namespace id
