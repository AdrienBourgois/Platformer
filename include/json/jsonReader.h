#ifndef JSON_READER_H_INCLUDED
#define JSON_READER_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include <fstream>

namespace id {
namespace json {

class JsonValue;

class JsonReader
{
public:
	JsonReader(std::string name = "partie1");
	~JsonReader();
	JsonReader(JsonReader const&) = delete;
	JsonReader(JsonReader&&) = delete;
	auto operator=(JsonReader const&) -> JsonReader& = delete;
	auto operator=(JsonReader&&) -> JsonReader& = delete;

	auto readBool(std::string key) -> bool;
	auto readString(std::string key) -> std::string;
	auto readNull(std::string key) -> bool;
	auto readNumber(std::string key) -> double;
	auto readStringArray(std::string key) -> std::vector<std::string>;
	auto readBoolArray(std::string key) -> std::vector<bool>;
	auto readNumberArray(std::string key) -> std::vector<double>;


//	auto loadNode() -> bool;

private:
	std::ifstream file;
};


} // namespace json
} // namespace id

#endif // JSON_READER_H_INCLUDED
