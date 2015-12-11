#ifndef EVENT_CAMERA_H_INCLUDED
#define EVENT_CAMERA_H_INCLUDED

#include <string>

#include "eventReceiver.h"

namespace id {

class Device;

namespace scene{
	class CameraSceneNode;
} // namespace scene

namespace event {

class EventCamera 
: public EventReceiver
{
public:
	EventCamera(Device* dev, std::string name, scene::CameraSceneNode* cam);
	virtual ~EventCamera();
	EventCamera(EventCamera const&) = delete;
	EventCamera(EventCamera&&) = delete;
	auto operator=(EventCamera const&) -> EventCamera& = delete;
	auto operator=(EventCamera&&) -> EventCamera& = delete;

	virtual auto eventListener() -> void;

private:
	scene::CameraSceneNode* cam;
};

} // namespace event
} // namespace id

#endif // EVENT_CAMERA_H_INCLUDED
