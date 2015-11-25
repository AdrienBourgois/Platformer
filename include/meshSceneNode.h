#ifndef MESH_SCENE_NODE_H_INCLUDED
#define MESH_SCENE_NODE_H_INCLUDED

#include <vector>

#include "sceneNode.h"

namespace id {

namespace video {
class Driver;
} // namespace video

namespace scene {

class Mesh;

class MeshSceneNode : public SceneNode
{
public:
	~MeshSceneNode();
	MeshSceneNode(MeshSceneNode const&) = delete;
	MeshSceneNode(MeshSceneNode&&) = delete;
	auto operator=(MeshSceneNode const&) = delete;
	auto operator=(MeshSceneNode&&) = delete;

	static 	auto createMeshSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, std::vector<GLfloat> shape = {}) -> MeshSceneNode*;

			auto getPrgId() const 			-> unsigned int { return _prg_id; }
			void setPrgId(unsigned int prg_id);

	virtual	auto getMesh() const 			-> Mesh*	{ return _mesh;	}
			auto setMesh(Mesh* mesh) 		-> void 	{ _mesh = mesh; }

	virtual auto draw(video::Driver* drv) 	-> void;

protected:
	MeshSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, std::vector<GLfloat> shape = {});
	
	Mesh* 			_mesh;
	unsigned int 	_prg_id;
};





} // namespace scene
} // namespace id

#endif // MESH_SCENE_NODE_H_INCLUDED
