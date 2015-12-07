#ifndef MESH_H_INCLUDED
#define MESH_H_INCLUDED

#include <vector>
#include <string>
#include <map>
#include <functional>
#include "material.h"

namespace id {

class Texture;

namespace video{
	class Driver;
}

namespace scene {

struct mesh_group
{
	std::string 		name;
	std::vector<float> 	data;
	unsigned int 		vao;
	unsigned int 		vbo;
	int 				dataSize() const { return this->data.size(); }
	std::string 		mtl;
};

class Mesh
{
public:
	~Mesh();
	Mesh(Mesh const&) = delete;
	Mesh(Mesh&&) = delete;
	auto operator=(Mesh const&) = delete;
	auto operator=(Mesh&&) = delete;

	static 	auto createMesh(std::string const& path, std::vector<GLfloat> const& shape, video::Driver* driver) -> Mesh*;

			auto getObjPath() const 		-> std::string const&		{ return _objPath;		}
			auto getVertex() const 			-> unsigned int 	{ return _vertex;		}
			auto getTriangle() const 		-> unsigned int 	{ return _triangle;		}
			auto getTextureCoord() const 	-> unsigned int 	{ return _textureCoord;	}
			auto getNormalCoord() const 	-> unsigned int 	{ return _normalCoord;	}
			auto getGroups() const 			-> std::map<std::string, mesh_group> const&	{ return _groups; }
			auto getMaterial() const 		-> Material* 		{ return _material; 	}
            auto foreachGroup(std::function<void(mesh_group&)> func) -> void
            {
                for (auto&& group : _groups)
                {
                    func(group.second);
                }
            }

			auto loadObj(std::string const& path) -> void;
			auto loadShape(std::vector<GLfloat>  const& shape) -> void;	

			//auto getGroups() 		-> std::map< std::string, mesh_group > { return _groups; }
	
	static 	auto deleteAllMeshes() 	-> void;
	
			auto getMaterial() 		-> Material* { return _material; }

private:
	Mesh(std::string const& path, std::vector<GLfloat> const& shape, video::Driver* driver);
	video::Driver* 						_driver;
	std::string 						_objPath;
	std::map< std::string, mesh_group > _groups;
	unsigned int						_vertex, _triangle, _textureCoord, _normalCoord;
	Material*							_material;
	static std::vector<Mesh*> 			_meshes;
};

} // namespace scene
} // namespace id

#endif // MESH_H_INCLUDED
