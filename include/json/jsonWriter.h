#ifndef JSON_WRITER_H_INCLUDED
#define JSON_WRITER_H_INCLUDED

#include <fstream>
#include <map>
#include <string>

namespace id {

namespace scene {
	class MeshSceneNode;
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

	auto writeNode(scene::MeshSceneNode* node, std::string fileName) -> void;
	auto writeAllNode(scene::SceneNode* root, std::string fileName) -> void;
	auto modifyLine(std::string keyLine, std::string newValue, std::string fileName) -> void;
	static int 		indentation;

};

} // namespace json
} // namespace id

#endif // JSON_WRITER_H_INCLUDED
