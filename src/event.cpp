#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>


#include "stateManager.h"
#include "event.h"
#include "enemy.h"
#include "player.h"
#include "txtLogger.h"
#include "maths/matrix.h"
#include "elementId.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}

namespace id {
namespace scene {

Event::Event(Player* player)
:player(player)
{
	logger->log("Initializing Event...", LL_DEBUG);

	logger->log("Event has been initialized.", LL_DEBUG);
}

Event::~Event()
{
	logger->log("Deleting Event...", LL_DEBUG);

	logger->log("Event deleted.",LL_DEBUG);
}

auto Event::playerEventReceiver() -> void 
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



	if (state[SDL_SCANCODE_S])
	{
		z += speed;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? z +=  speedrun : z += speed;
	}

	else if (state[SDL_SCANCODE_W])
	{
		z -= speed;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? z -= speedrun : z -= speed;
	}

	if (state[SDL_SCANCODE_D])
	{
		x +=  speed;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? x += speedrun : x += speed;
	}

	else if (state[SDL_SCANCODE_A])
	{
		x -= speed;
		player->setEntityState(STATE_WALKING);
		state[SDL_SCANCODE_R] ? x -= speedrun : x -= speed;
		
	}
/*	// ===== debug =======
	if (state[SDL_SCANCODE_J])
		delete player;

*/	// ===== end ====



	if (state[SDL_SCANCODE_Q])
	{
		rotz -= speed;
		player->setEntityState(STATE_WALKING);
	}


	else if (state[SDL_SCANCODE_E])
	{
		rotz += speed;
		player->setEntityState(STATE_WALKING);	
	}


	if (state[SDL_SCANCODE_R])
	{
		speed = speedrun;
		player->setEntityState(STATE_RUNNING);
	}
	
	if (player->entityIsMovement() == true)
		player->setPosition({x, y, z});

		player->setRotation({rotx, roty, rotz});
	
	if (player->getHp() == 0)
		player->setEntityState(STATE_DEAD);



	if (player->getEntityState() == STATE_DEAD)
		std::cout << player->getEntityState() << std::endl;

}

}//namespace scene
}//namespace id
