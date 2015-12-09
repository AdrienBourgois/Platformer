#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>

#include "stateManager.h"
#include "event.h"
#include "enemy.h"
#include "player.h"
#include "txtLogger.h"
#include "maths/matrix.h"
#include "elementId.h"
#include "json/jsonReader.h"

#include <iostream>

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace scene {

Event::Event(Player* player)
:player(player)
{
	logger->log("Initializing Event...", LL_DEBUG);

	loadKeys();

	logger->log("Event has been initialized.", LL_DEBUG);
}

Event::~Event()
{
	logger->log("Deleting Event...", LL_DEBUG);

	logger->log("Event deleted.",LL_DEBUG);
}

auto Event::eventReceiver(float deltaTime) -> void 
{
	if (!player)
		return;

	if (player)
		player->setEntityState(STATE_STANDING);
		
	const Uint8* state = SDL_GetKeyboardState(nullptr);

	player->entitySpeed();

	float speedrun = player->getSpeedRun();
	float speed = player->getSpeed();
	float x = player->getPosition().val[0];
	float y = player->getPosition().val[1];
	float z = player->getPosition().val[2];
	float rotx = player->getRotation().val[0];
	float roty = player->getRotation().val[1];
	float rotz = player->getRotation().val[1];

	if (state[this->scancodeKeys["Backward"]])
	{
		z += speed * deltaTime;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? z +=  speedrun * deltaTime : z += speed * deltaTime;
	}
	else if (state[this->scancodeKeys["Forward"]])
	{
		z -= speed * deltaTime;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? z -= speedrun * deltaTime : z -= speed * deltaTime;
	}

	if (state[this->scancodeKeys["Strafe_right"]])
	{
		x +=  speed * deltaTime;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? x += speedrun * deltaTime : x += speed * deltaTime;
	}
	else if (state[this->scancodeKeys["Strafe_left"]])
	{
		x -= speed * deltaTime;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? x -= speedrun * deltaTime : x -= speed * deltaTime;
	}

	if (state[this->scancodeKeys["Turn_left"]])
	{
		rotz -= speed * deltaTime;
		player->setEntityState(STATE_WALKING);
	}
	else if (state[this->scancodeKeys["Turn_right"]])
	{
		rotz += speed * deltaTime;
		player->setEntityState(STATE_WALKING);	
	}

	if (state[this->scancodeKeys["Run"]])
	{
		speed = speedrun;
		player->setEntityState(STATE_RUNNING);
	}
	
	if (player->entityIsMovement() == true)
	{
		player->setPosition({x, y, z});
		player->setRotation({rotx, roty, rotz});
	}

	if (player->getHp() == 0)
		player->setEntityState(STATE_DEAD);
}
auto Event::loadKeys() -> void
{
	json::JsonReader jsonReader;
	std::map<std::string, std::string> stringKeys = jsonReader.loadKeyBinding("bindingKey");

	for (auto it = stringKeys.begin(); it != stringKeys.end(); ++it)
	{
		this->scancodeKeys[it->first] = SDL_GetScancodeFromName(it->second.c_str());
	}
}

} // end namespace scene
} // end namespace id
