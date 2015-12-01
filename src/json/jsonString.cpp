#include "txtLogger.h"
#include "json/jsonObject.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

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
	serializeAsString();
}

} // namespace json 
} // namespace id
