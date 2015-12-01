#include "json/jsonWriter.h"
#include "json/jsonValue.h"
#include "json/jsonObject.h"
#include "txtLogger.h"

#include <iostream>
namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json { 

JsonWriter::JsonWriter(std::string name)
:file(("./assets/json/" + name + ".json").c_str(), std::ios_base::out), indentation(0)
{
	logger->log("Creating JsonWriter...", LL_DEBUG);

	logger->log("JsonWriter has been created.");
}

JsonWriter::~JsonWriter()
{
	logger->log("Deleting JsonWriter");

	file.close();

	logger->log("JsonWriter has been deleted");
}

auto JsonWriter::indent() -> void
{
	for (int i = 0; i < indentation; ++i)
		std::cout << "\t";
}

auto JsonWriter::write(JsonObject* obj) -> void
{
	serializeAsObject(obj->getMapValue());
}

auto JsonWriter::serializeAsObject(std::map<std::string, JsonValue*> mapValue) -> void
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

auto JsonWriter::serializeAsArray(std::vector<JsonValue*> arrayValue) -> void
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

auto JsonWriter::serializeAsString(std::string str) -> void
{
	std::cout << "\"" << str << "\"";
}

auto JsonWriter::serializeAsBool(bool boolean) -> void
{
	if (boolean)
		std::cout << "true";
	else
		std::cout << "false";
}

auto JsonWriter::serializeAsNumber(long double number) -> void
{
	std::cout << number;
}

auto JsonWriter::serializeAsNull() -> void
{
	std::cout << "null";
}
							    
} // namespace json
} // namespace id
