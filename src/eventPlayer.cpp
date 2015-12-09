#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "txtLogger.h"
#include "eventPlayer.h"
#include "eventReceiver.h"
#include "device.h"
#include "player.h"
#include "stateManager.h"
#include "elementId.h"
#include "json/jsonReader.h"

namespace {
	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace event {

EventPlayer::EventPlayer(Device* dev, std::string name, scene::Player* player)
: EventReceiver(dev, name), player(player)
{
	logger->log("Creating EventPlayer...", LL_INFO);

	loadKeys();

	logger->log("EventPlayer created", LL_INFO);
}
EventPlayer::~EventPlayer()
{
	logger->log("Deleting EventPlayer...", LL_INFO);

	logger->log("EventPlayer deleted", LL_INFO);
}
auto EventPlayer::eventListener() -> void
{	
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (this->player)
	{
		player->entitySpeed();

		float deltaTime = dev->getDeltaTime();
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
}
auto EventPlayer::loadKeys() -> void
{
    json::JsonReader jsonReader;
    std::map<std::string, std::string> stringKeys = jsonReader.loadKeyBinding("bindingKey");

    for (auto it = stringKeys.begin(); it != stringKeys.end(); ++it)
    {
        this->scancodeKeys[it->first] = SDL_GetScancodeFromName(it->second.c_str());
    }
}

} // end namespace event

} // end namespace id
