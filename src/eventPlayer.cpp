#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "logger.h"
#include "eventPlayer.h"
#include "eventReceiver.h"
#include "device.h"
#include "player.h"
#include "stateManager.h"
#include "elementId.h"
#include "json/jsonReader.h"
#include "json/jsonWriter.h"

namespace id {
namespace event {

EventPlayer::EventPlayer(Device* dev, std::string name, scene::Player* player)
: EventReceiver(dev, name), player(player)
{
	LOG(L_INFO ,"Creating EventPlayer...");

	loadKeys();

	LOG(L_INFO ,"EventPlayer created");
}
EventPlayer::~EventPlayer()
{
	LOG(L_INFO ,"Deleting EventPlayer...");

	this->player = nullptr;

	LOG(L_INFO ,"EventPlayer deleted");
}
auto EventPlayer::eventListener() -> void
{	
	const Uint8* key = SDL_GetKeyboardState(nullptr);
	if (this->player)
	{
		this->player->entitySpeed();

		float deltaTime = this->dev->getDeltaTime();
		float speedrun = this->player->getSpeedRun();
		float speed = this->player->getSpeed();
		float x = this->player->getPosition().val[0];
		float y = this->player->getPosition().val[1];
		float z = this->player->getPosition().val[2];
		float rotX = this->player->getRotation().val[0];
		float rotY = this->player->getRotation().val[1];
		float rotZ = this->player->getRotation().val[2];

		if (key[this->scancodeKeys["Backward"]])
   		{
	   	 	z += speed * deltaTime;
			if (!this->player->getEntityState()->checkEntityState(STATE_RUNNING))
   	 	   	{
				this->player->getEntityState()->setEntityState(STATE_WALKING);
				z += speed * deltaTime;
    	   		}
			else
				z +=  speedrun * deltaTime;    	
		}
   	 	else if (key[this->scancodeKeys["Forward"]])
    		{
    			z -= speed * deltaTime;
    	   
			if (!this->player->getEntityState()->checkEntityState(STATE_RUNNING)) 
			{
				this->player->getEntityState()->setEntityState(STATE_WALKING);
				z -= speed * deltaTime;
		    	}
			else
				z -= speedrun * deltaTime;
    		}
		if (key[this->scancodeKeys["Strafe_right"]])
	   	{
	       		x +=  speed * deltaTime;
			if (!this->player->getEntityState()->checkEntityState(STATE_RUNNING))
		   	{
				this->player->getEntityState()->setEntityState(STATE_WALKING);
				x += speed * deltaTime;
			}
			else
		    	    	x += speedrun * deltaTime;
		}
		else if (key[this->scancodeKeys["Strafe_left"]])
   	 	{
    			x -= speed * deltaTime;
			if (!this->player->getEntityState()->checkEntityState(STATE_RUNNING))
	    		{
				this->player->getEntityState()->setEntityState(STATE_WALKING);
    	    			x -= speed * deltaTime;
			}
			else
				x -= speedrun * deltaTime;
	    	}
	
		if (key[this->scancodeKeys["Turn_left"]])
		{
	       		rotY += deltaTime * 2.f;
		        this->player->getEntityState()->setEntityState(STATE_WALKING);
	    	}
		else if (key[this->scancodeKeys["Turn_right"]])
		{
	        	rotY -= deltaTime * 2.f;
		        this->player->getEntityState()->setEntityState(STATE_WALKING);
		}

		if (key[this->scancodeKeys["Run"]])
	    	{
       			speed = speedrun;
        		this->player->getEntityState()->setEntityState(STATE_RUNNING);
    		}
		else
			this->player->getEntityState()->setEntityState(STATE_WALKING);

    	if (this->player->entityIsMovement() == true)
    	{
    	    this->player->setPosition({x, y, z});
    	    this->player->setRotation({rotX, rotY, rotZ});
    	}

		if (key[this->scancodeKeys["Quick_save"]])
		{
			json::JsonWriter jsonWriter;
			jsonWriter.writeAllNode(this->dev->getSceneManager()->getRootNode(), "partie1");
		}

    	if (player->getHp() == 0)
    	    this->player->getEntityState()->setEntityState(STATE_DEAD);
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
auto EventPlayer::deletePlayer() -> void
{
	this->player = nullptr;
}

} // end namespace event

} // end namespace id
