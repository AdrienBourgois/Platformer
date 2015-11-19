#ifndef SAVE_TO_JSON_H_INCLUDED
#define SAVE_TO_JSON_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
#include <map>


namespace id {
namespace scene {
	class MeshSceneNode;
} // namespace scene

class JsonValue
{
	public :
		JsonValue(std::string name);
		~JsonValue();

	

	template<typename T, typename U>
	auto tryParseValue(T a, U b) -> void;

	template<typename T>
	auto tryParseArray(T a) -> void;

	auto tryParseString(std::string a, std::string b) -> void;

	auto openObject(std::string = "") -> void;
	auto closeObject(bool = true) -> void;
	auto cleanJson() -> void;

	auto openArray(std::string) -> void;
	auto closeArray() -> void;

	static auto saveToJson(scene::MeshSceneNode* node) -> void;

	private :
		std::fstream _file;
};

#include "templateSaveJson.inl"

} // namespace id

#endif // SAVE_TO_JSON_H_INCLUDED
