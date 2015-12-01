#ifndef JSON_ARRAY_H_INCLUDED
#define JSON_ARRAY_H_INCLUDED

#include <vector>
#include "json/jsonValue.h"

namespace id {
namespace json {

class JsonArray
:public JsonValue
{
public:
	JsonArray();
	virtual ~JsonArray();
	JsonArray(JsonArray const&);
	JsonArray(JsonArray&&) = default;
	auto operator=(JsonArray const&) -> JsonArray& = default;
	auto operator=(JsonArray&&) -> JsonArray& = default;

	auto addInArray(JsonValue* val) -> void;
	virtual auto serialize() -> void override;

	auto getArrayValue() const -> std::vector<JsonValue*> { return arrayValue; }

private:
	std::vector<JsonValue*> arrayValue;

};

} // namespace json
} // namespace id

#endif // JSON_ARRAY_H_INCLUDED
