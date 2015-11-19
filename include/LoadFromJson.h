#ifndef LOAD_FROM_JSON_H
#define LOAD_FROM_JSON_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <vector>

namespace id {

namespace scene{
	class SceneManager;
	class MeshSceneNode;
} // namespace scene

class Texture;

class JsonLoad
{
	public :
		JsonLoad(std::string fileName);
		~JsonLoad() = default;

	
				template<typename T>
				auto getValue(std::string name) -> std::vector<T>;

				auto createTexture(std::vector<std::string> vec) -> void;
				auto applyTexture(scene::MeshSceneNode* mesh, std::vector<std::string> name, std::vector<std::string> mapKd) -> void;
				auto cleanString(std::vector<std::string> vec) -> std::vector<std::string>;
		static 	auto loadFromJson(std::string file_name, scene::SceneManager* smgr) -> void;

	private:
		std::string 			fileName;
		std::vector<Texture*> 	texVec;
};

#include "TemplateLoadJson.inl"

} // namespace id

#endif
