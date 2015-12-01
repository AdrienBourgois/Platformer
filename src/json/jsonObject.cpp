#include "txtLogger.h"
#include "json/jsonObject.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

JsonObject::JsonObject()
{
	logger->log("Creating JsonObject...", LL_DEBUG);

	logger->log("JsonObject has been created.");
}

JsonObject::JsonObject(JsonObject const& obj)
:JsonObject()
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
	serializeAsObject(mapValue);
}

} // namespace json 
} // namespace id
