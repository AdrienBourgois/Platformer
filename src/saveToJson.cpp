#include <fstream>

#include "saveToJson.h"
#include "meshSceneNode.h"
#include "mesh.h"
#include "texture.h"

namespace id {

JsonValue::JsonValue(std::string name)
:_file(("./assets/json/" + name + ".json").c_str(), std::ios_base::out)
{
}	

JsonValue::~JsonValue()
{
	_file.close();
}		

auto JsonValue::tryParseString(std::string a, std::string b) -> void
{
	_file << "\"" << a << "\": \"" << b << "\"," << std::endl;
}

auto JsonValue::openObject(std::string string) -> void
{
	if (string == "")
		_file << "{";
	else
		_file << "\"" << string << "\": " << "{";
}

auto JsonValue::closeObject(bool comma) -> void
{
	long pos = _file.tellp();
	_file.seekp(pos-2);
if (comma == true)
		_file << "}," << std::endl;
	else 
		_file << "}" << std::endl;
}

auto JsonValue::openArray(std::string a) -> void
{
	_file << "\"" << a << "\": [" << std::endl;
}

auto JsonValue::closeArray() -> void
{
	long pos = _file.tellp();
	_file.seekp(pos-2);
	_file << "]," << std::endl;
	
}

auto JsonValue::saveToJson(scene::MeshSceneNode* node) -> void
{
	int error_mkdir = std::system("mkdir assets/json -p");
	(void)error_mkdir;

	JsonValue Json(node->getName());

	Json.openObject();
	Json.tryParseString("Name", node->getName());
	Json.tryParseString("Parent_name", node->getParent()->getName());
	Json.tryParseValue("Number_of_children", node->getChildrens().size());
	Json.tryParseValue("Visibility", node->getVisible());
	Json.openArray("Transformation");
	for (unsigned int i = 0; i<16; ++i)
		Json.tryParseArray(node->getTransformation().val[i]);
	Json.closeArray();
	Json.tryParseString("Obj_path", node->getMesh()->getObjPath());
	Json.tryParseValue("Number_of_mesh_group", node->getMesh()->getGroups().size());
	Json.openArray("Mesh_groups");
	for (auto&& map : node->getMesh()->getGroups())
	{
		Json.openObject();
		Json.tryParseString("group_name", map.second.name);
		Json.tryParseValue("Data_size", map.second.dataSize());
		Json.tryParseString("Material_used", map.second.mtl);
		Json.closeObject();
	}
	Json.closeArray();
	Json.tryParseValue("Number_of_material", node->getMesh()->getMaterial()->getMTLs().size());
	Json.openArray("Materials");
	for (auto&& map : node->getMesh()->getMaterial()->getMTLs())
	{
		Json.openObject();
		Json.tryParseString("Material_name", map.second.name);
		Json.tryParseString("Map_Kd", map.second.map_Kd);
		if (map.second.texture)
		{
			Json.openObject();
			Json.tryParseString("texture_path", map.second.texture->getFileName());
			Json.closeObject();	
		}
		Json.closeObject();
	}
	Json.closeArray();
	Json.closeObject(false);
}

} // namespace id
