#include "txtLogger.h"
#include "json/jsonNumber.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

JsonNumber::JsonNumber(double number)
:number(number)
{
	logger->log("Creating JsonNumber...", LL_DEBUG);
	jsonVal.push_back(this);
	logger->log("JsonNumber has been created.");
}

JsonNumber::~JsonNumber()
{
	logger->log("Deleting JsonNumber...", LL_DEBUG);

	logger->log("JsonNumber has been deleted.");
}

auto JsonNumber::serialize() -> std::string
{
	return std::to_string(number);
}

} // namespace json 
} // namespace id
