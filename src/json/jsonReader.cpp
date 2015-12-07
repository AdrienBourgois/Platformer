#include <sstream>
#include <fstream>

#include "txtLogger.h"
#include "json/jsonValue.h"
#include "json/jsonReader.h"
#include "fileUtility.h"
#include "device.h"
#include "sceneManager.h"
#include "meshSceneNode.h"
#include "sceneNode.h"
#include "maths/matrix.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();

auto findNode(std::string name, id::scene::SceneNode* node) -> id::scene::SceneNode*
{
	if (node->getName() == name)
		return node;
	for (auto&& nod : node->getChildrens())
		if(findNode(name, nod))
			return findNode(name, nod);
	return nullptr;

}

}

namespace id {
namespace json {

JsonReader::JsonReader()
{
	logger->log("Creating jsonReader...", LL_DEBUG);

	logger->log("Jsonreader has been created.");
}

JsonReader::~JsonReader()
{
	logger->log("Deleting JsonReader...", LL_DEBUG);

	logger->log("JsonReader has been deleted.");
}

auto JsonReader::readBool(std::string key, std::string fileName) -> std::vector<bool>
{

	std::ifstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);

	std::string line;
	std::string keyFile;
	std::vector<bool> vecBool;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					if ( id::FileUtility::getStringWithoutExtra(keyFile) == "true" )
						vecBool.push_back(true);
					else 
						vecBool.push_back(false);
				}
			}
		}
	}
	file.close();
	return vecBool;
}

auto JsonReader::readString(std::string key, std::string fileName) -> std::vector<std::string>
{
	std::ifstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);
	std::string line;
	std::string keyFile;
	std::string finalstr;
	std::vector<std::string> vecString;

	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					finalstr = id::FileUtility::getStringWithoutExtra(keyFile);
					vecString.push_back(finalstr);
				}
			}
		}
	}
	file.close();	
	return vecString;

}

auto JsonReader::readNull(std::string key, std::string fileName) -> std::vector<bool>
{

	std::ifstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);

	std::string line;
	std::string keyFile;
	std::string finalstr;
	std::vector<bool> vecNull;	
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					finalstr = id::FileUtility::getStringWithoutExtra(keyFile); 
					if (finalstr == "null")
						vecNull.push_back(true);
					else 
						vecNull.push_back(false);
				}
			}
		}
		file.close();
	}
	return vecNull;



}

auto JsonReader::readNumber(std::string key, std::string fileName) -> std::vector<float>
{
	std::ifstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);

	std::string line;
	std::string keyFile;
	std::string finalNumber;
	std::vector<float> vecNum;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile;
					finalNumber = id::FileUtility::getNumberStringFromString(keyFile);
					vecNum.push_back(std::stof(finalNumber));
				}
			}
		}
		file.close();
	}
	return vecNum;
}

auto JsonReader::readStringArray(std::string key, std::string fileName) -> std::vector<std::vector<std::string>>
{
	std::ifstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);

	std::string line;
	std::string keyFile;
	std::string finalstr;
	std::vector<std::vector<std::string>> vecVal;
	unsigned int i = 0;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile; // ignore '['
					sstr >> keyFile;
					while (keyFile != "]")
					{
						finalstr = id::FileUtility::getStringWithoutExtra(keyFile);
						vecVal[i].push_back(finalstr);
						sstr >> keyFile;
					}
					++i;
				}
			}
		}
		file.close();
	}
	return vecVal;
}

auto JsonReader::readBoolArray(std::string key, std::string fileName) -> std::vector<std::vector<bool>>
{
	std::ifstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);

	std::string line;
	std::string keyFile;
	std::string finalstr;
	std::vector<std::vector<bool>> vecVal;
	unsigned int i = 0;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile; // ignore '['
					sstr >> keyFile;
					while (keyFile != "]")
					{
						finalstr = id::FileUtility::getStringWithoutExtra(keyFile);
						
						if (finalstr == "true")
							vecVal[i].push_back(true);
						else
							vecVal[i].push_back(false);
						sstr >> keyFile;
					}
					++i;
				}
			}
		}
		file.close();
	}
	return vecVal;
}

auto JsonReader::readNumberArray(std::string key, std::string fileName) -> std::vector<std::vector<float>>
{
	std::ifstream file;
	file.open(("./assets/json/" + fileName + ".json").c_str(), std::ios_base::out);

	std::string line;
	std::string keyFile;
	std::string finalNumber;
	std::vector<std::vector<float>> vecVal;
	unsigned int i = 0;
	if (file.is_open())
	{
		while(std::getline(file, line))
		{
			if (line.size() > 0)
			{
				std::stringstream sstr(line);
				sstr >> keyFile;
				if (keyFile == "\"" + key + "\"")
				{
					sstr >> keyFile; // ignore ':'
					sstr >> keyFile; // ignore '['
					sstr >> keyFile;
					std::vector<float> vecDouble;
					while (*keyFile.begin() != ']')
					{
						finalNumber = id::FileUtility::getNumberStringFromString(keyFile);
						vecDouble.push_back(std::stof(finalNumber));
						sstr >> keyFile;
					}
					++i;
					vecVal.push_back(vecDouble);
				}
			}
		}
		file.close();
	}
	return vecVal;
}

auto JsonReader::loadAllNode(Device* device, std::string fileName) ->void 
{
	std::vector<std::string> name = readString("name", fileName);
	std::vector<std::string> parent = readString("parent", fileName);
	std::vector<std::string> objPath = readString("objPath", fileName);
	std::vector<std::vector<float>> matrix = readNumberArray("transformation", fileName);	
	for (unsigned int i = 0; i < name.size(); ++i)
	{
		scene::SceneNode* node = findNode(parent[i], device->getSceneManager()->getRootNode());
		id::scene::MeshSceneNode* mesh = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), node, name[i], "pos3d_tex2d", objPath[i]);

		id::maths::Matrix4 mat = id::maths::Matrix4({matrix[i][0],matrix[i][1],matrix[i][2],matrix[i][3],matrix[i][4],matrix[i][5],matrix[i][6],matrix[i][7],matrix[i][8],matrix[i][9],matrix[i][10],matrix[i][11],matrix[i][12],matrix[i][13],matrix[i][14],matrix[i][15]});

		mesh->setTransformation(mat);
	}
}

/*
auto JsonReader::loadKeyBinding(std::string fileName) -> std::map<std::string, std::string>
{
	std::map<std::string, std::string> mapKeyAffect;
	
}
*/
} // namespace json
} // namespace id


