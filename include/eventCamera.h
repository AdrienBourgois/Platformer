#ifndef EVENT_CAMERA_H_INCLUDED
#define EVENT_CAMERA_H_INCLUDED

#include <string>

#include "eventReceiver.h"
#include "device.h"
#include "cameraSceneNode.h"

namespace id {
namespace event {

class EventCamera : public EventReceiver
{
public:
	EventCamera(Device* dev, std::string name, scene::CameraSceneNode* cam);
	virtual ~EventCamera();

	virtual auto eventListener() -> void;

private:
	scene::CameraSceneNode* cam;
};

} // end namespace event

} // end namespace id

#endif // EVENT_CAMERA_H_INCLUDED
