#ifndef JSON_VALUE_H_INCLUDED
#define JSON_VALUE_H_INCLUDED

#include <string>
#include <vector>

namespace id {
namespace json {

class JsonValue
{
public:
	virtual ~JsonValue() = default;
	JsonValue(JsonValue const&) = delete;
	JsonValue(JsonValue&&) = delete;
	auto operator=(JsonValue const&) -> JsonValue& = delete;
	auto operator=(JsonValue&&) -> JsonValue& = delete;

	virtual auto serialize() -> std::string { return "";}
	static auto deleteAllJsonValue() -> void;

protected:
	JsonValue() = default;	
	static std::vector<JsonValue*> jsonVal;
};

} // namespace json
} // namespace id

#endif // JSON_VAlUE_H_INCLUDED
