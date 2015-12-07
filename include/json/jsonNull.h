#ifndef JSON_NULL_H_INCLUDED
#define JSON_NULL_H_INCLUDED

#include "json/jsonValue.h"

namespace id {
namespace json {

class JsonNull
:public JsonValue
{
public:
	JsonNull();
	virtual ~JsonNull();
	JsonNull(JsonNull const&) = default;
	JsonNull(JsonNull&&) = default;
	auto operator=(JsonNull const&) -> JsonNull& = default;
	auto operator=(JsonNull&&) -> JsonNull& = default;

	virtual auto serialize() -> std::string override;

};

} // namespace json
} // namespace id

#endif // JSON_NULL_H_INCLUDED
