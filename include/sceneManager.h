#ifndef SCENE_MANAGER_H_INCLUDED
#define SCENE_MANAGER_H_INCLUDED

#include <GL/glew.h>
#include <vector>
#include <map>

namespace id {

namespace video {
class Driver;
} // namespace video

namespace scene {
class Mesh;
class SceneNode;
class CameraSceneNode;

class SceneManager
{
public:
	~SceneManager();

static auto createSceneManager(video::Driver* driver) -> SceneManager*;
	auto draw() 								-> void;
	auto getRootNode() const 					-> SceneNode* 				{ return _root; }
	auto getDriver() const 						-> video::Driver* 			{ return _driver; }
	auto getActiveCamera() const 				-> CameraSceneNode* 		{ return _cur_cam; }
	auto setActiveCamera(CameraSceneNode* cam) 	-> void 					{ _cur_cam = cam; }
	auto addToRender(SceneNode* node, GLuint prg_id) -> void;
	auto eraseRender(SceneNode* node, GLuint prg_id) -> void;
	auto clearAllNodeExceptRootCam(SceneNode* root) -> void;
	
	auto addToDeletionQueue(SceneNode* node) 	-> void;
	auto clearDeletionQueue() 					-> void;
private:
	SceneManager(video::Driver* driver);
	SceneNode* 				_root;
	video::Driver* 			_driver;
	CameraSceneNode* 		_cur_cam;
	
	std::vector<SceneNode*> _deletion_queue;
	
	std::map<GLuint, std::vector<SceneNode*>> _render_nodes;
};

} // namespace scene
} // namespace id

#endif // SCENE_MANAGER_H_INCLUDED
