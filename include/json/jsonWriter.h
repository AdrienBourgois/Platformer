#ifndef JSON_WRITER_H_INCLUDED
#define JSON_WRITER_H_INCLUDED

#include <fstream>
#include <string>
#include <map>
#include <vector>

namespace id {
namespace json {

class JsonValue;
class JsonObject;

class JsonWriter
{
public:
	JsonWriter(std::string name = "partie1");
	virtual ~JsonWriter();
	JsonWriter(JsonWriter const&) = delete;
	JsonWriter(JsonWriter&&) = delete;
	auto operator=(JsonWriter const&) -> JsonWriter& = delete;
	auto operator=(JsonWriter&&) -> JsonWriter& = delete;
	
	auto serializeAsObject(std::map<std::string, JsonValue*>) -> void;
	auto serializeAsArray(std::vector<JsonValue*>) -> void;
	auto serializeAsString(std::string) -> void;
	auto serializeAsBool(bool) -> void;
	auto serializeAsNumber(long double) -> void;
	auto serializeAsNull() -> void;

	auto indent() -> void;
	auto write(JsonObject* obj) -> void; 

protected:
	std::fstream 	file;
	int 		indentation;
};

} // namespace json
} // namespace id

#endif // JSON_WRITER_H_INCLUDED
