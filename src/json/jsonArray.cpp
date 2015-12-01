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

	logger->log("JsonArray has been created.");
}

JsonArray::JsonArray(JsonArray const& arr)
:JsonArray()
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
	serializeAsArray(arrayValue);
}

} // namespace json 
} // namespace id
