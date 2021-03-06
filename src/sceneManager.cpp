#include "sceneManager.h"
#include "sceneNode.h"
#include "mesh.h"
#include "driver.h"
#include "cameraSceneNode.h"
#include "logger.h"

namespace id {
namespace scene {

auto SceneManager::createSceneManager(video::Driver* driver) -> SceneManager*
{
	SDL_assert(driver);

	auto* smgr = new (std::nothrow) SceneManager(driver);
	if (!smgr)
	{
		LOG(L_ERROR, "Failed at creating Scene Manager in SceneManager::createSceneManager(video::Driver* driver)");
		SDL_assert(smgr);
	}

	return smgr;
}

SceneManager::SceneManager(video::Driver* driver)
: _driver(driver), _cur_cam(nullptr)
{
	LOG(L_DEBUG, "Creating SceneManager...");

	_root = SceneNode::createSceneNode(this, 0, "ROOT");
	_deletion_queue = std::vector<SceneNode*>();
	_render_nodes = std::map<GLuint, std::vector<SceneNode*>>();

	LOG(L_INFO, "SceneManager has been created.");
}

SceneManager::~SceneManager()
{
	LOG(L_DEBUG, "Deleting SceneManager...");

	delete _root;
	_root = nullptr;

	_render_nodes.clear();
	Mesh::deleteAllMeshes();

	LOG(L_INFO, "SceneManager has been deleted.");
}

auto SceneManager::draw() -> void
{
	for (auto prg_pass = _render_nodes.begin(); prg_pass != _render_nodes.end(); ++prg_pass)
	{
		_driver->useProgram(prg_pass->first);
		maths::Matrix4 proj = _cur_cam->getProjection();
		maths::Matrix4 view = _cur_cam->AbsoluteTransformation().getInverse();
		std::vector<SceneNode*>::iterator node = prg_pass->second.begin();
		for (; node != prg_pass->second.end(); ++node)
		{
			maths::Matrix4 model = (*node)->AbsoluteTransformation();

			_driver->AttachUniformMatrix4(prg_pass->first, "model", model);
			_driver->AttachUniformMatrix4(prg_pass->first, "view", view);
			_driver->AttachUniformMatrix4(prg_pass->first, "proj", proj);
			(*node)->draw(_driver);
		
		}
		_driver->useProgram(0);
	}
}

auto SceneManager::addToRender(SceneNode* node, GLuint prg_id) -> void
{
	SDL_assert(node);

	char str[500];

	sprintf(str, "Adding node [%s]\twith program [%i] to render...", node->getName().c_str(), prg_id);
	LOG(L_INFO, str);

	_render_nodes[prg_id].push_back(node);

	LOG(L_INFO, "Texture has been added to node");
}

auto SceneManager::eraseRender(SceneNode* node, GLuint prg_id) -> void
{
	SDL_assert(node);

	LOG(L_DEBUG, "Erasing render...");

	std::vector<SceneNode*>::iterator it = _render_nodes.find(prg_id)->second.begin();
	std::vector<SceneNode*>::iterator it_end = _render_nodes.find(prg_id)->second.end();
	
	for (; it != it_end; ++it)
	{
		if ((*it) == node)
		{
			it = _render_nodes.find(prg_id)->second.erase(it);
		}
	}

	LOG(L_INFO, "Render has been erased.");
}

auto SceneManager::clearAllNodeExceptRootCam(SceneNode* root) -> void
{
	for (auto&& node : root->getChildrens())
	{
		clearAllNodeExceptRootCam(node);
		if (node != _cur_cam)
		{
			delete node;
			node = nullptr;
		}
	}
}



auto SceneManager::addToDeletionQueue(SceneNode* node) -> void
{
	SDL_assert(node);

	_deletion_queue.push_back(node);
}

auto SceneManager::clearDeletionQueue() -> void
{
	SceneNode* node_to_delete;
	for (std::vector<SceneNode*>::iterator it = _deletion_queue.begin(); it != _deletion_queue.end(); ++it)
	{
		node_to_delete = *it;
		delete node_to_delete;
		node_to_delete = nullptr;
	}
	_deletion_queue.clear();
}

} // namespace scene
} // namespace id
