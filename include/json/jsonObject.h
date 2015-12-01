#ifndef JSON_OBJECT_H_INCLUDED
#define JSON_OBJECT_H_INCLUDED

#include <map>
#include "json/jsonValue.h"

namespace id {
namespace json {

class JsonObject
:public JsonValue
{
public:
	JsonObject();
	virtual ~JsonObject();
	JsonObject(JsonObject const&);
	JsonObject(JsonObject&&) = default;
	auto operator=(JsonObject const&) -> JsonObject& = default;
	auto operator=(JsonObject&&) -> JsonObject& = default;

	auto addInObject(std::string, JsonValue*) -> void;
	virtual auto serialize() -> void override;

	auto getMapValue() const -> std::map<std::string, JsonValue*> { return mapValue; } 

private:
	std::map<std::string, JsonValue*> mapValue;
};

} // namespace json
} // namespace id

#endif // JSON_OBJECT_H_INCLUDED
