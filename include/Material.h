#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <map>
#include "Texture.h"

namespace id {

struct mtl
{
public:
	std::string name;
	std::string map_Kd;
	Texture* 	texture;
};

class Material
{
public:
	Material(std::string path);
	~Material();

	auto LoadMTL(std::string path) 			-> void;
	auto getTextureFromMTL(std::string mtl) -> Texture*;
	auto getMTLs() 							-> std::map<std::string, mtl>& 	{ return _mtls; }
	auto getMTL(std::string name) 			-> mtl* 						{ return &_mtls[name]; }

	auto setTexture(std::string name, std::string map_Kd, Texture* texture)	-> void;
private:
	
	std::map< std::string, mtl > _mtls;
};

} // namespace id

#endif
