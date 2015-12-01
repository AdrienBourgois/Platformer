#include "txtLogger.h"
#include "json/jsonNull.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

JsonNull::JsonNull()
{
	logger->log("Creating JsonNull...", LL_DEBUG);
	jsonVal.push_back(this);
	logger->log("JsonNull has been created.");
}

JsonNull::~JsonNull()
{
	logger->log("Deleting JsonNull...", LL_DEBUG);

	logger->log("JsonNull has been deleted.");
}

auto JsonNull::serialize() -> std::string 
{
	return "null";
}

} // namespace json 
} // namespace id
