#include <string>
#include <iostream>
#include <vector>

#include "shaders.h"
#include "meshSceneNode.h"
#include "cameraSceneNode.h"
#include "mesh.h"
#include "sceneManager.h"
#include "driver.h"
#include "txtLogger.h"
#include "texture.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace scene {


auto MeshSceneNode::createMeshSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> MeshSceneNode*
{
	SDL_assert(scn);

	MeshSceneNode* meshSceneNode = new (std::nothrow)MeshSceneNode(scn, parent, name, shader, path);
	if (!meshSceneNode)
		logger->log("failed at creating meshSceneNode in MeshSceneNode::createMeshSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader)", LL_WARNING);

	return meshSceneNode;

}

MeshSceneNode::MeshSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)
: SceneNode(scn, parent, name), _mesh(nullptr)
{

	scn->getDriver()->getShader()->loadProgram(shader);
    _prg_id = scn->getDriver()->getShader()->getPrg(shader);


	_mesh = Mesh::createMesh(path, scn->getDriver());
 
	_scn->addToRender(this, _prg_id);
 
	logger->log("MeshSceneNode has been created.");
}

MeshSceneNode::~MeshSceneNode()
{
	std::string str = "MeshSceneNode [" + _name + "] deleting...";

	logger->log(str, LL_DEBUG);
	_scn->eraseRender(this, _prg_id);
	logger->log("MeshSceneNode has been deleted.");
}

void MeshSceneNode::setPrgId(unsigned int prg_id)
{
	_scn->eraseRender(this, _prg_id);
	_prg_id = prg_id;
	_scn->addToRender(this, _prg_id);
}

auto MeshSceneNode::draw(video::Driver* driver) -> void
{
	SDL_assert(driver);

	for (auto& v : _mesh->getGroups())
	{
		Material* material = _mesh->getMaterial();
		Texture* texture = material->getTextureFromMTL(v.second.mtl);
		unsigned int texture_id = 0;
		if (texture)
			texture_id = texture->getID();
		driver->ChangeTexture(texture_id);
		driver->drawTriangles(v.second.vao, v.second.vbo, v.second.dataSize());
	}
	SceneNode::draw(driver);
}

} // namespace scene
} // namespace id
