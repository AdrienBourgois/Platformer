#ifndef JSON_BOOL_H_INCLUDED
#define JSON_BOOL_H_INCLUDED

#include "json/jsonValue.h"

namespace id {
namespace json {

class JsonBool
:public JsonValue
{
public:
	JsonBool(bool boolean = true);
	virtual ~JsonBool();
	JsonBool(JsonBool const&) = default;
	JsonBool(JsonBool&&) = default;
	auto operator=(JsonBool const&) -> JsonBool& = default;
	auto operator=(JsonBool&&) -> JsonBool& = default;

	virtual auto serialize() -> std::string override;
			auto setBool(bool bol) -> JsonBool* {boolean = bol; return this;} 

private:
	bool boolean;
};

} // namespace json
} // namespace id

#endif // JSON_BOOL_H_INCLUDED
