#include <GL/glew.h>
#include <sstream>

#include "mesh.h"
#include "driver.h"
#include "maths/matrix.h"
#include "logger.h"
#include "texture.h"
#include "fileUtility.h"

namespace id {
namespace scene {

std::vector<Mesh*> Mesh::_meshes = std::vector<Mesh*>();

auto Mesh::createMesh(std::string const& path, video::Driver* driver) -> Mesh*
{
	SDL_assert(driver);

	if (path != "")
		for (auto&& mesh : Mesh::_meshes)
		{
			if (mesh->getObjPath() == path)
				{
					LOG(L_INFO, "Didn't create new Mesh in Mesh::createMesh(std::string const& path, std::string const& tex_path, video::Driver* driver) because mesh already exist.");
					return mesh;
				}
		}
	
	Mesh* mesh = new (std::nothrow) Mesh(path, driver);
	if (!mesh)
		LOG(L_WARNING, "Failed at creating Mesh in Mesh::createMesh(std::string const& path, std::string const& tex_path, video::Driver* driver)");


	return mesh;
}

Mesh::Mesh(std::string const& path, video::Driver* driver)
: _driver(driver), _objPath(path), _material(nullptr)
{
	LOG(L_DEBUG, "Creating Mesh...");
	
	if (_objPath != "")
	{
		loadObj(_objPath);
	}
	for (auto& v : _groups)
		_driver->genVertexObject(v.second.dataSize() * sizeof(v.second.data[0]), &v.second.data[0], &v.second.vbo, &v.second.vao);
	
	_meshes.push_back(this);
	LOG(L_INFO, "Mesh has been created.");
}


Mesh::~Mesh()
{
	LOG(L_DEBUG, "Deleting mesh...");
	
	for (auto& v : _groups)
		_driver->deleteBuffer(&v.second.vbo);
	delete _material;
	
	LOG(L_INFO, "Mesh has been deleted.");
}

auto Mesh::deleteAllMeshes() -> void
{
	for (std::vector<Mesh*>::iterator it = _meshes.begin(); it != _meshes.end(); ++it)
		delete *it;
}

auto Mesh::loadObj(std::string const& path) -> void
{
	LOG(L_DEBUG, "loading obj...");

	std::ifstream file(path);
	
	if (!file.good())
	{
		LOG(L_WARNING, "Loading obj failed !");
		return;
	}
	
	// Obj contents
	std::vector<std::vector<float>> vertices;
	std::vector<std::vector<float>> texcoord;
	std::vector<std::vector<float>> vertnorm;
	std::map< std::string, std::vector<std::vector<std::string>> > faces;
	std::string cur_group = "";
	
	std::string line;
	std::string type;
	
	while (std::getline(file, line))
	{
		if (line.size() > 0)
		{
			std::stringstream line_stream(line);
			line_stream >> type;
			
			if (type == "mtllib")
			{
				std::string mtl_file;
				line_stream >> mtl_file;
				
				_material = new Material(FileUtility::getPathWithoutFileName(path) + mtl_file);
			}
			else if (type == "g")
			{
				line_stream >> cur_group;
			}
			else if (type == "v")
			{
				float x,y,z;
				line_stream >> x >> y >> z;
				vertices.push_back({x, y, z});
			}
			else if (type == "vt")
			{
				float x,y;
				line_stream >> x >> y;
				texcoord.push_back({x, y});
			}
			else if (type == "vn")
			{
				float x,y,z;
				line_stream >> x >> y >> z;
				vertnorm.push_back({x, y, z});
			}
			else if (type == "f")
			{
				int num_vertex = 3;
				std::vector<std::string> data_face;
				for (int i = 0; i < num_vertex; ++i)
				{
					std::string data_face_vertex;
					line_stream >> data_face_vertex;
					data_face.push_back(data_face_vertex);
				}
				faces[cur_group].push_back(data_face);
			}
			else if (type == "usemtl")
			{
				std::string mtl_name;
				line_stream >> mtl_name;
				_groups[cur_group].mtl = mtl_name;
			}
		}
	}

	
	for (auto const& grp : faces)
	{
		std::string grp_name = grp.first;
		for (auto const& f : grp.second)
		{
			int num_vertex = 3;
			std::vector<std::string> data_face = f;
			for (int i = 0; i < num_vertex; ++i)
			{
				int v, vt, vn;
				std::sscanf(data_face[i].c_str(), "%i/%i/%i", &v, &vt, &vn);
				for (int j = 0; j < 3; ++j)
					_groups[grp_name].data.push_back( vertices[v-1][j] );
				
					_groups[grp_name].data.push_back(  texcoord[vt-1][0] );
					_groups[grp_name].data.push_back(  texcoord[vt-1][1] );
				for (int j = 0; j < 3; ++j)
					_groups[grp_name].data.push_back( vertnorm[vn-1][j] );
			}
		}
	}
	
	char str[50];
	sprintf(str, "Vertex count : %lu", vertices.size());
	LOG(L_INFO, str);

	sprintf(str, "Triangle count : %lu", vertices.size() / 3);
	LOG(L_INFO, str);

	sprintf(str, "Texcoord count : %lu", texcoord.size());
	LOG(L_INFO, str);

	sprintf(str, "Normals count : %lu", vertnorm.size());
	LOG(L_INFO, str);

	_vertex 		= vertices.size();
	_triangle 		= _vertex / 3;
	_textureCoord 	= texcoord.size();
	_normalCoord 	= vertnorm.size(); 

	LOG(L_INFO, "Obj has been loaded.");

}

} // namespace scene
} // namespace id
