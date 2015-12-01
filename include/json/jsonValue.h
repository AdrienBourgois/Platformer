#ifndef JSON_VALUE_H_INCLUDED
#define JSON_VALUE_H_INCLUDED

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

	virtual auto serialize() -> void;

protected:
	JsonValue() = default;	
};

} // namespace json
} // namespace id

#endif // JSON_VAlUE_H_INCLUDED
