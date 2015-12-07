#include <sstream>

#include "meshSceneNode.h"
#include "sceneNode.h"
#include "mesh.h"
#include "json/jsonWriter.h"
#include "json/jsonValue.h"
#include "json/jsonObject.h"
#include "json/jsonNumber.h"
#include "json/jsonBool.h"
#include "json/jsonNull.h"
#include "json/jsonArray.h"
#include "json/jsonString.h"
#include "txtLogger.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

int id::json::JsonWriter::indentation = 0;

namespace id {
namespace json { 

JsonWriter::JsonWriter()
{
	logger->log("Creating JsonWriter...", LL_DEBUG);

	logger->log("JsonWriter has been created.");
}

JsonWriter::~JsonWriter()
{
	logger->log("Deleting JsonWriter");

	logger->log("JsonWriter has been deleted");
}

auto JsonWriter::indent() -> std::string
{
	std::string str = "";
	for (int i = 0; i < indentation; ++i)
		str += "\t";
	return str;
}

auto JsonWriter::write(JsonObject* obj, std::ofstream& file) -> void
{

	std::map<std::string, JsonValue*> mapValue = obj->getMapValue();

	if (!mapValue.empty())
	{
		indentation++;

		for (auto&& val : mapValue)
		{
			file << indent();
			file << "\"" << val.first << "\" : ";
			file << val.second->serialize();
			file << ",\n";
		}

		--indentation;
		file << indent();
	}
}

auto JsonWriter::writeNode(scene::SceneNode* node, std::ofstream& file) -> void
{
	JsonObject* obj  = new JsonObject;
	JsonObject* objNode = new JsonObject;

	if (node->getParent())
		objNode->addInObject("parent", new JsonString(node->getParent()->getName()));
	else
 		objNode->addInObject("parent", new JsonNull);

	objNode->addInObject("name", new JsonString(node->getName()));
	JsonArray* matrix = new JsonArray;
	for (unsigned int i = 0; i < 16; ++i)
			matrix->addInArray(new JsonNumber(node->getTransformation().val[i]));
	objNode->addInObject("transformation", matrix);
	if (dynamic_cast<scene::MeshSceneNode*>(node))
		objNode->addInObject("objPath", new JsonString(dynamic_cast<scene::MeshSceneNode*>(node)->getMesh()->getObjPath()));
	obj->addInObject("node", objNode);
	write(obj, file);
	JsonValue::deleteAllJsonValue();
}

auto JsonWriter::writeAllNode(scene::SceneNode* root, std::string fileName) -> void
{
	std::ofstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);
	file << "{" << std::endl;


	for (auto&& child : root->getChildrens())
	{
		writeNode(child, file);
		writeAllNode(child, file);
	}

	file.seekp(-2, file.cur); 
	file << "\n}" << std::endl;
	file.close();
}

auto JsonWriter::writeAllNode(scene::SceneNode* node, std::ofstream& file) -> void
{
	for (auto&& child : node->getChildrens())
	{
		writeNode(child, file);
		writeAllNode(child, file);
	}
}

auto JsonWriter::saveDefaultBindKey(std::string fileName) -> void
{
	std::ofstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);
	file << "{" << std::endl;

	JsonObject* objKey  = new JsonObject;
	objKey->addInObject("forward", new JsonString("w"));
	objKey->addInObject("backward", new JsonString("s"));
	objKey->addInObject("turn_right", new JsonString("d"));
	objKey->addInObject("turn_left", new JsonString("a"));
	objKey->addInObject("strafe_right", new JsonString("e"));
	objKey->addInObject("strafe_left", new JsonString("q"));
	objKey->addInObject("jump", new JsonString("space"));
	objKey->addInObject("shoot", new JsonString("j"));
	objKey->addInObject("run", new JsonString("r"));
	objKey->addInObject("pause", new JsonString("p"));

	write(objKey, file);

	file.seekp(-2, file.cur); 
	file << "\n}" << std::endl;
	file.close();

}

auto JsonWriter::modifyLine(std::string keyLine, std::string newValue, std::string fileName) -> void
{
	std::ifstream fileRead;
	fileRead.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::in);

	std::string line;
	std::string key;
	std::string copyStream;
	std::string completeFile;

	while(std::getline(fileRead, line))
	{
		std::stringstream sstr(line);
		sstr >> key;
		if (key == "\"" + keyLine + "\"")
		{
			for (unsigned int i = 0; i < line.size(); ++i)
				if (line[i] == '\t')
					completeFile += "\t";
			completeFile += key;
			sstr >> key; // ignore ":"
			completeFile += " " + key;
			sstr >> key;
			if (key[0] == '"')
				copyStream = " \"" + newValue + "\"";
			else
				copyStream = " " + newValue;	

			if (key[key.size()-1] == ',')
				copyStream += ',';

			completeFile += copyStream + "\n";
		}
		else
		{
			completeFile += line + "\n";
		}
	}
	fileRead.close();
	
	std::ofstream fileWrite;
	fileWrite.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);
	fileWrite << completeFile;
	fileWrite.close();
}

} // namespace json
} // namespace id
