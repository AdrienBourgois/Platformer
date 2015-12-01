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

	JsonNumber(double number);

	virtual auto serialize() -> std::string override;

private:
	double number;
};

} // namespace json
} // namespace id

#endif // JSON_NUMBER_H_INCLUDED
