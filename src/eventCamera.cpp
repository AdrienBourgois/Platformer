#include <SDL2/SDL.h>
#include <string>

#include "txtLogger.h"
#include "eventCamera.h"
#include "eventReceiver.h"
#include "device.h"
#include "cameraSceneNode.h"

#include <iostream>

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace event {

EventCamera::EventCamera(Device* dev, std::string name, scene::CameraSceneNode* cam)
: EventReceiver(dev, name), cam(cam)
{
	logger->log("Creating EventCamera...", LL_INFO);

	logger->log("EventCamera created", LL_INFO);
}
EventCamera::~EventCamera()
{
	logger->log("Deleting EventCamera...", LL_INFO);

	this->cam = nullptr;

	logger->log("EventCamera deleted", LL_INFO);
}
auto EventCamera::eventListener() -> void
{
	const Uint8* key = SDL_GetKeyboardState(nullptr);
	if (this->cam)
	{
		float deltaTime = this->dev->getDeltaTime();
		float x = this->cam->getPosition().val[0];
		float y = this->cam->getPosition().val[1];
		float z = this->cam->getPosition().val[2];
		float rotX = this->cam->getRotation().val[0];
		float rotY = this->cam->getRotation().val[1];
		float rotZ = this->cam->getRotation().val[2];

		if (key[SDL_SCANCODE_W])
			z -= deltaTime * 5.f;
		if (key[SDL_SCANCODE_S])
			z += deltaTime * 5.f;
		if (key[SDL_SCANCODE_D])
			rotY += deltaTime * 5.f;
		if (key[SDL_SCANCODE_A])
			rotY -= deltaTime * 5.f;
		if (key[SDL_SCANCODE_E])
			x += deltaTime * 5.f;
		if (key[SDL_SCANCODE_Q])
			x -= deltaTime * 5.f;
		if (key[SDL_SCANCODE_UP])
			y += deltaTime * 5.f;
		if (key[SDL_SCANCODE_DOWN])
			y -= deltaTime * 5.f;

		this->cam->setPosition({x, y, z});
		this->cam->setRotation({rotX, rotY, rotZ});
	}
}

} // end namespace event

} // end namespace id
