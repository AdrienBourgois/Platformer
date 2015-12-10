#ifndef JSON_WRITER_H_INCLUDED
#define JSON_WRITER_H_INCLUDED

#include <fstream>
#include <map>
#include <string>

namespace id {

namespace scene {
	class SceneNode;
} // namespace scene

namespace json {

class JsonValue;
class JsonObject;

class JsonWriter
{
public:
	JsonWriter();
	virtual ~JsonWriter();
	JsonWriter(JsonWriter const&) = delete;
	JsonWriter(JsonWriter&&) = delete;
	auto operator=(JsonWriter const&) -> JsonWriter& = delete;
	auto operator=(JsonWriter&&) -> JsonWriter& = delete;
	
	auto indent() -> std::string;
	auto write(JsonObject* obj, std::string fileName) -> void;
	auto writeInObject(JsonObject* obj, std::ofstream& file) -> void; 
	

	auto writeNode(scene::SceneNode* node, std::ofstream& file) -> void;
	auto writeNode(scene::SceneNode* node, std::string fileName) -> void;
	auto writeAllNode(scene::SceneNode* root, std::string const& fileName) -> void;
	auto writeAllNode(scene::SceneNode* node, std::ofstream& file) -> void;

	auto saveDefaultBindKey(std::string fileName = "bindingKey") -> void;
	auto saveDefaultResolution(std::string fileName = "resolutionScreen") -> void;

	auto modifyLineByNameSearch(std::string keyLine, std::string newValue, std::string fileName = "bindingKey") -> void;
	auto modifyLineByValueSearch(std::string value, std::string newValue, std::string fileName = "bindingKey") -> void;
	auto checkExistingValue(std::string value, std::string fileName = "bindingKey") -> bool;

	static int 		indentation;

};

} // namespace json
} // namespace id

#endif // JSON_WRITER_H_INCLUDED
