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

	int error_mkdir = std::system("mkdir assets/json2 -p");
	(void)error_mkdir;

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

auto JsonWriter::write(JsonObject* obj, std::string fileName) -> void
{
	std::ofstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);
	file << "{\n";	

	std::map<std::string, JsonValue*> mapValue = obj->getMapValue();

	unsigned int i = 1;
	unsigned int j = mapValue.size();

	if (!mapValue.empty())
	{
		indentation++;

		for (auto&& val : mapValue)
		{
			file << indent();
			file << "\"" << val.first << "\" : ";
			file << val.second->serialize();
			if (i == j)
				file << "\n";
			else	
				file << ",\n";
			++i;
		}

		--indentation;
		file << indent();
	}
	file << "}"; 
}

auto JsonWriter::writeInObject(JsonObject* obj, std::ofstream& file) -> void
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
	else
		objNode->addInObject("objPath", new JsonNull());
	obj->addInObject("node", objNode);
	writeInObject(obj, file);
	JsonValue::deleteAllJsonValue();
}

auto JsonWriter::writeNode(scene::SceneNode* node, std::string fileName) -> void
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
	write(obj, fileName);
	JsonValue::deleteAllJsonValue();
}

auto JsonWriter::writeAllNode(scene::SceneNode* root, std::string const& fileName) -> void
{
	std::ofstream file;
	file.open(("./assets/json/" + fileName + ".json"), std::ofstream::binary);
	file << "{" << std::endl;
	for (auto&& child : root->getChildrens())
	{
		if (child->getName() != "Cam")
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
	JsonObject* objKey  = new JsonObject;
	objKey->addInObject("Forward", new JsonString("W"));
	objKey->addInObject("Backward", new JsonString("S"));
	objKey->addInObject("Turn_right", new JsonString("D"));
	objKey->addInObject("Turn_left", new JsonString("A"));
	objKey->addInObject("Strafe_right", new JsonString("E"));
	objKey->addInObject("Strafe_left", new JsonString("Q"));
	objKey->addInObject("Jump", new JsonString("Space"));
	objKey->addInObject("Shoot", new JsonString("J"));
	objKey->addInObject("Run", new JsonString("R"));
	objKey->addInObject("Pause", new JsonString("P"));

	write(objKey, fileName);
}

auto JsonWriter::saveDefaultResolution(std::string fileName) -> void
{

	JsonObject* objResol  = new JsonObject;
	objResol->addInObject("Width", new JsonNumber(1280));
	objResol->addInObject("Height", new JsonNumber(720));

	write(objResol, fileName);

	modifyLineByValueSearch("1280.000000", "1280", "resolutionScreen");
	modifyLineByValueSearch("720.000000", "720", "resolutionScreen");
	
}




auto JsonWriter::modifyLineByNameSearch(std::string keyLine, std::string newValue, std::string fileName) -> void
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
			{
				copyStream = " \"" + newValue + "\"";
				if (key[key.size()-1] != '"' && key[key.size()-1] != ',')
				{
					std::string keySequel;
					sstr >> keySequel;
					key = key + " " + keySequel;
				}
			}
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

auto JsonWriter::modifyLineByValueSearch(std::string value, std::string newValue, std::string fileName) -> void
{
	std::ifstream fileRead;
	fileRead.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::in);

	std::string line;
	std::string key;
	std::string copyStream;
	std::string completeFile;
	std::string copyValue;
	while(std::getline(fileRead, line))
	{
		std::stringstream sstr(line);
		sstr >> key;
			
		for (unsigned int i = 0; i < line.size(); ++i)
			if (line[i] == '\t')
				completeFile += "\t";
		completeFile += key + " "; // get Name

		if (key.size() != 1)
		{
			sstr >> key;
			completeFile += key + " "; // get ":"
			sstr >> key;
			if (key[0] == '"')
			{
				copyValue = "\"" + value + "\"";
				if (key[key.size()-1] != '"' && key[key.size()-1] != ',')
				{
					std::string keySequel;
					sstr >> keySequel;
					key = key + " " + keySequel;
				}
			}	
			else
				copyValue = value;
			
			if (key == copyValue || key == copyValue + "," )
			{

				if (key[0] == '"')
					newValue = "\"" + newValue + "\"";

				copyStream = newValue;
				if (key[key.size()-1] == ',')
					copyStream += ',';

				completeFile += copyStream + "\n";
			}
			else
			{
				completeFile += key + "\n";
			}
		}
		else
			completeFile += "\n";
	}
	fileRead.close();
	
	std::ofstream fileWrite;
	fileWrite.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);
	fileWrite << completeFile;
	fileWrite.close();
}

auto JsonWriter::checkExistingValue(std::string value, std::string fileName) -> bool
{
	std::ifstream fileRead;
	fileRead.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::in);

	std::string line;
	std::string key;

	while(std::getline(fileRead, line))
	{
		std::stringstream sstr(line);
		sstr >> key; // ignore name
		sstr >> key; // ignore ":"
		sstr >> key;
		if (key[0] == '"')
		{
			if (key[key.size()-1] != '"' && key[key.size()-1] != ',')
			{
				std::string keySequel;
				sstr >> keySequel;
				key = key + " " + keySequel;
			}

			if (key == "\"" + value + "\"" || key == "\"" + value + "\"," )
				return true;
		}
		else
			if (key == value || key == value + ",")
				return true;
	}
	fileRead.close();
	return false;
}

} // namespace json
} // namespace id
