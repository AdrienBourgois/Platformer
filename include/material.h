#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
#include <map>
#include "texture.h"

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

#endif // MATERIAL_H_INCLUDED
