#include "json/jsonValue.h"

namespace id {
namespace json {

std::vector<id::json::JsonValue*> id::json::JsonValue::jsonVal;

auto JsonValue::deleteAllJsonValue() -> void
{
	for (auto&& val : jsonVal)
		delete val;
	jsonVal.clear();
}

} // namespace json
} // namespace id
