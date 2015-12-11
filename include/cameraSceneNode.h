#ifndef CAMERA_SCENE_NODE_H_INCLUDED
#define CAMERA_SCENE_NODE_H_INCLUDED

#include <string>

#include "sceneNode.h"

namespace id {

namespace video {
	class Driver;
} // namespace video

namespace scene {

class CameraSceneNode 
: public SceneNode
{
public:
	static auto createCameraSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, float fovy, float ratio, float near, float far) -> CameraSceneNode*;
	
	virtual ~CameraSceneNode();
	CameraSceneNode(CameraSceneNode const&) = delete;
	CameraSceneNode(CameraSceneNode&&) = delete;
	auto operator=(CameraSceneNode const&) -> CameraSceneNode& = delete;
	auto operator=(CameraSceneNode&&) -> CameraSceneNode& = delete;

	auto getFOV() const 	-> float 		{ return _fovy;  }
	auto getRatio() const 	-> float 		{ return _ratio; }
	auto getNear() const 	-> float 		{ return _near;  }
	auto getFar() const 	-> float 		{ return _far;   }
	
	auto setFOV(float fovy) 	-> void;
	auto setRatio(float ratio) 	-> void;
	auto setNear(float near)	-> void;
	auto setFar(float far)		-> void;
	
	auto moveForward(float speed) -> void;

	auto getProjection() const -> maths::Matrix4 const&	{ return _proj; }
	
private:
	CameraSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, float fovy, float ratio, float near, float far);

	float _fovy;
	float _ratio;
	float _near;
	float _far;

	maths::Matrix4	_proj;
};

} // namespace scene
} // namespace id


#endif // CAMERA_SCENE_NODE_H_INCLUDED
