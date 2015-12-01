#ifndef JSON_STRING_H_INCLUDED
#define JSON_STRING_H_INCLUDED

#include "json/jsonValue.h"

namespace id {
namespace json {

class JsonString
:public JsonValue
{
public:
	JsonString();
	virtual ~JsonString();
	JsonString(JsonString const&) = default;
	JsonString(JsonString&&) = default;
	auto operator=(JsonString const&) -> JsonString& = default;
	auto operator=(JsonString&&) -> JsonString& = default;

	JsonString(std::string str);

	virtual auto serialize() -> std::string override;

private:
	std::string str;
};

} // namespace json
} // namespace id

#endif // JSON_STRING_H_INCLUDED
