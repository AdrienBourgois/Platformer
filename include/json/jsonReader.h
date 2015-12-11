#ifndef JSON_READER_H_INCLUDED
#define JSON_READER_H_INCLUDED

#include <string>
#include <map>
#include <vector>

namespace id {

class Device;

namespace json {

class JsonValue;

class JsonReader
{
public:
	JsonReader();
	~JsonReader();

	auto readBool(std::string key, std::string fileName = "partie1") -> std::vector<bool>;
	auto readString(std::string key, std::string fileName = "partie1") -> std::vector<std::string>;
	auto readNull(std::string key, std::string fileName = "partie1") -> std::vector<bool>;
	auto readNumber(std::string key, std::string fileName = "partie1") -> std::vector<float>;
	auto readStringArray(std::string key, std::string fileName = "partie1") -> std::vector<std::vector<std::string>>;
	auto readBoolArray(std::string key, std::string fileName = "partie1") -> std::vector<std::vector<bool>>;
	auto readNumberArray(std::string key, std::string fileName = "partie1") -> std::vector<std::vector<float>>;

	auto loadAllNode(Device* device, std::string fileName = "partie1") -> void;
	auto loadKeyBinding(std::string fileName = "bindingKey") -> std::map<std::string, std::string>;
	auto loadScreenResolution(std::string fileName = "resolutionScreen") -> std::map<std::string, float>;

};
} // namespace json
} // namespace id

#endif // JSON_READER_H_INCLUDED
