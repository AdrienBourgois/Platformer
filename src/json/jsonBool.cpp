#include "txtLogger.h"
#include "json/jsonBool.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace json {

JsonBool::JsonBool(bool boolean)
:boolean(boolean)
{
	logger->log("Creating JsonBool...", LL_DEBUG);
	jsonVal.push_back(this);
	logger->log("JsonBool has been created.");
}

JsonBool::~JsonBool()
{
	logger->log("Deleting JsonBool...", LL_DEBUG);

	logger->log("JsonBool has been deleted.");
}

auto JsonBool::serialize() -> std::string
{
	if (boolean)
		return "true";
	else
		return "false";

}

} // namespace json 
} // namespace id
