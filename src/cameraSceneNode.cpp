#include <SDL2/SDL.h>

#include "cameraSceneNode.h"
#include "maths/matrix.h"
#include "logger.h"


namespace id {
namespace scene {

auto CameraSceneNode::createCameraSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, float fovy, float ratio, float near, float far) -> CameraSceneNode*
{
	SDL_assert(scn && parent);

	auto* cam = new (std::nothrow) CameraSceneNode(scn, parent, name, fovy, ratio, near, far);
	if (!cam)
	{
		LOG(L_ERROR,"Failed at creating Camera Scene Node in CameraSceneNode::createCameraSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, float fovy, float ratio, float near, float far)");
		#ifdef _DEBUG
		SDL_assert(cam);
		#endif
	}

	return cam;
}

CameraSceneNode::CameraSceneNode(SceneManager* scn, SceneNode* parent, std::string const& name, float fovy, float ratio, float near, float far)
: SceneNode(scn, parent, name), _fovy(fovy), _ratio(ratio), _near(near), _far(far)
{
	LOG(L_INFO,"Creating CameraSceneNode...");
	
	_proj = maths::Matrix4::perspective(fovy,ratio,near,far);
	
	if (scn->getActiveCamera() == nullptr)
		scn->setActiveCamera(this);

	LOG(L_INFO,"CameraSceneNode has been created.");
}

CameraSceneNode::~CameraSceneNode()
{
	LOG(L_INFO,"Deleting CameraSceneNode...");

	LOG(L_INFO,"CameraSceneNode has been deleted.");
}
	
auto CameraSceneNode::setFOV(float fovy) -> void
{
	_fovy = fovy;
	_proj = maths::Matrix4::perspective(_fovy,_ratio,_near,_far);
}
auto CameraSceneNode::setRatio(float ratio) -> void
{
	_ratio = ratio;
	_proj = maths::Matrix4::perspective(_fovy,_ratio,_near,_far);
}
auto CameraSceneNode::setNear(float near) -> void
{
	_near = near;
	_proj = maths::Matrix4::perspective(_fovy,_ratio,_near,_far);
}
auto CameraSceneNode::setFar(float far) -> void
{
	_far = far;
	_proj = maths::Matrix4::perspective(_fovy,_ratio,_near,_far);
}

auto CameraSceneNode::moveForward(float speed) -> void
{
	_transformation.setPosition(_transformation.Forward().getNormalized() * speed);
}

} // namespace scene
} // namespace id
