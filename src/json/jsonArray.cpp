#include "txtLogger.h"
#include "json/jsonArray.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

JsonArray::JsonArray()
{
	logger->log("Creating JsonArray...", LL_DEBUG);
	jsonVal.push_back(this);
	logger->log("JsonArray has been created.");
}

JsonArray::JsonArray(JsonArray const& arr)
:JsonArray()
{
	logger->log("Creating JsonArray by copy...", LL_DEBUG);	
	arrayValue = arr.getArrayValue();
	jsonVal.push_back(this);

	logger->log("JsonArray has been created by copy.");
}

JsonArray::~JsonArray()
{
	logger->log("Deleting JsonArray...", LL_DEBUG);

	arrayValue.clear();

	logger->log("JsonArray has been deleted.");
}

auto JsonArray::addInArray(JsonValue* val) -> void
{
	arrayValue.push_back(val);
}

auto JsonArray::serialize() ->std::string 
{
	std::string str;

	str =  "[ ";

	unsigned int i = 1;
	unsigned int j = arrayValue.size();
	for (auto&& val : arrayValue)
	{
		str += val->serialize();
		if (i != j)
			str += ", ";
		++i;
	}
	str += " ]";
	return str;

}

} // namespace json 
} // namespace id
