#include "txtLogger.h"
#include "json/jsonObject.h"
#include "json/jsonWriter.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();

	auto indent() -> std::string
	{
		std::string str = "";
		for (int i = 0; i < id::json::JsonWriter::indentation; ++i)
			str += "\t";
		return str;
	}
}

namespace id {
namespace json {

JsonObject::JsonObject()
{
	logger->log("Creating JsonObject...", LL_DEBUG);

	jsonVal.push_back(this);

	logger->log("JsonObject has been created.");
}

JsonObject::JsonObject(JsonObject const& obj)
:JsonObject()
{
	logger->log("Creating JsonObject by copy...", LL_DEBUG);
	
	mapValue = obj.getMapValue();
	jsonVal.push_back(this);

	logger->log("JsonObject has been created by copy.");
}

JsonObject::~JsonObject()
{
	logger->log("Deleting JsonObject...", LL_DEBUG);

	mapValue.clear();

	logger->log("JsonObject has been deleted.");
}

auto JsonObject::addInObject(std::string str, JsonValue* val) -> void
{
	mapValue[str] = val;
}

auto JsonObject::serialize() -> std::string 
{
	std::string str;

	if (!mapValue.empty())
	{
		str = "{\n";
		++id::json::JsonWriter::indentation;

		unsigned int i = 1;
		unsigned int j = mapValue.size();
		for (auto&& val : mapValue)
		{
			str += indent();
			str += "\"" + val.first + "\" : ";
			str += val.second->serialize();
			if ( i == j)
				str += "\n";
			else
				str += ",\n";
			++i;
		}

		--id::json::JsonWriter::indentation;
		str += indent();
	}
	else
		str += "{";	
	str += "}";
	return str;
}

} // namespace json 
} // namespace id
