#ifndef JSON_WRITER_H_INCLUDED
#define JSON_WRITER_H_INCLUDED

#include <fstream>
#include <map>
#include <string>

namespace id {

namespace scene {
	class MeshSceneNode;
} // namespace scene

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
	
	auto indent() -> std::string;
	auto write(JsonObject* obj) -> void; 

	auto writeNode(scene::MeshSceneNode* node) -> void;

	static int 		indentation;
private:
	std::ofstream 	file;

};

} // namespace json
} // namespace id

#endif // JSON_WRITER_H_INCLUDED
