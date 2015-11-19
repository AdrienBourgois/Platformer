#include <iostream>

#include "loadFromJson.h"
#include "meshSceneNode.h"
#include "device.h"
#include "sceneManager.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include "txtLogger.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {

JsonLoad::JsonLoad(std::string fileName)
:fileName(fileName)
{
}


auto JsonLoad::loadFromJson(std::string file_name, scene::SceneManager* smgr) -> void
{
	SDL_assert(smgr);

	JsonLoad json(file_name);

	std::vector<std::string> objPath = json.getValue<std::string>("\"Obj_path\":");
	std::vector<std::string> matName = json.getValue<std::string>("{\"Material_name\":");
	std::vector<std::string> texPath = json.getValue<std::string>("{\"texture_path\":");
	std::vector<std::string> mapKds  = json.getValue<std::string>("\"Map_Kd\":");

	objPath = json.cleanString(objPath);
	matName = json.cleanString(matName);
	mapKds  = json.cleanString(mapKds);
	texPath = json.cleanString(texPath);

	json.createTexture(texPath);	
		
	scene::MeshSceneNode* mesh = scene::MeshSceneNode::createMeshSceneNode(smgr, smgr->getRootNode(), file_name, "pos3d_tex2d", objPath.front());

	json.applyTexture(mesh, matName, mapKds);	
}

auto JsonLoad::cleanString(std::vector<std::string> vec) -> std::vector<std::string>
{

	for (auto&& str : vec)
	{
		if ((*str.begin()) == '"')
		{
			str.erase(str.begin());
			unsigned int str_size = str.size();
			for (unsigned int i = 0; i < str_size; ++i)
			{
				if (str[i] == '"')
					str.erase(str.begin() + i, str.end());				
			}
		}
	}
	return vec;
}

auto JsonLoad::createTexture(std::vector<std::string> vec) -> void
{
	for (auto&& tex : vec)
	{
		Texture* texture = Texture::addTexture(tex);
		if (!texture->load())
			logger->log("Couldn't load texture in loadFromJson", LL_WARNING);
		texVec.push_back(texture);
	}
}

auto JsonLoad::applyTexture(scene::MeshSceneNode* mesh, std::vector<std::string> name, std::vector<std::string> mapKd) -> void
{
	for (unsigned int i = 0; i < mapKd.size(); ++i)
		mesh->getMesh()->getMaterial()->setTexture(name[i], mapKd[i], texVec[i]);
}

} // namespace id 
