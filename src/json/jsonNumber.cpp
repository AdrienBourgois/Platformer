#include "txtLogger.h"
#include "json/jsonNumber.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

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
	serializeAsNumber(number);
}

} // namespace json 
} // namespace id
