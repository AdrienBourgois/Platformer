#ifndef JSON_NUMBER_H_INCLUDED
#define JSON_NUMBER_H_INCLUDED

#include "json/jsonValue.h"

namespace id {
namespace json {

class JsonNumber
:public JsonValue
{
public:
	JsonNumber() = default;
	virtual ~JsonNumber();
	JsonNumber(JsonNumber const&) = default;
	JsonNumber(JsonNumber&&) = default;
	auto operator=(JsonNumber const&) -> JsonNumber& = default;
	auto operator=(JsonNumber&&) -> JsonNumber& = default;

	JsonNumber(float number);

	virtual auto serialize() -> std::string override;

private:
	float number;
};

} // namespace json
} // namespace id

#endif // JSON_NUMBER_H_INCLUDED
