#include <SDL2/SDL.h>
#include "Material.h"
#include "TxtLogger.h"
#include <sstream>
#include "FileUtility.h"
#include <iostream>

namespace {
    id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {

Material::Material(std::string path)
{
	logger->log("Creating Material...", LL_DEBUG);
	
	this->LoadMTL(path);
	
	logger->log("Material has been created.");
}

Material::~Material()
{
	logger->log("Deleting material...", LL_DEBUG);
	
	
	logger->log("Material has been deleted.");
}

auto Material::LoadMTL(std::string path) -> void
{
	logger->log("loading mtl...", LL_DEBUG);
	std::ifstream file(path);

    if (!file.good())
    {
		std::string error = "Loading mtl failed ! [" + path + "]";
        logger->log(error, LL_WARNING);
        return;
    }
	// Mtl contents
	std::string cur_mtl = "";
	//
	std::string line;
	std::string type;
	
	while (std::getline(file, line))
    {
        if (line.size() > 0)
        {
            std::stringstream line_stream(line);
            line_stream >> type;
			if (type == "newmtl")
			{
				line_stream >> cur_mtl;
			}
			else if (type == "map_Kd")
			{
				std::string map_Kd;
				line_stream >> map_Kd;
				std::string texture_path = FileUtility::getPathWithoutFileName(path) + map_Kd;
				auto* _texture = Texture::addTexture(texture_path);
				if (!_texture->load())
					logger->log("Couldn't load texture in Mesh::Mesh()", LL_WARNING);
				_mtls[cur_mtl] = {cur_mtl, map_Kd, _texture};
			}
		}
	}
	
	logger->log("Mtl has been loaded.");
}

auto Material::getTextureFromMTL(std::string mtl) -> Texture*
{
	return _mtls[mtl].texture;
}

auto Material::setTexture(std::string name, std::string map_Kd, Texture* texture) -> void
{
	SDL_assert(texture);

	_mtls[name].map_Kd = map_Kd;
	_mtls[name].texture = texture;
}

} // namespace id
