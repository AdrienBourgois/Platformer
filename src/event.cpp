#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cmath>

#include "device.h"
#include "stateManager.h"
#include "elementId.h"
#include "sceneNode.h"
#include "event.h"
#include "player.h"
#include "txtLogger.h"
#include "entity.h"
#include "maths/matrix.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}


namespace id {

namespace scene {


Event::Event(Player* player, Enemy* enemy)
:player(player), enemy(enemy)
{
	logger->log("Creating Event...", LL_DEBUG);


	logger->log("Event has been created.", LL_INFO);	
}


Event::~Event()
{
	logger->log("Deleting Event...", LL_DEBUG);

	logger->log("Event has been deleted.", LL_INFO);

}

auto	Event::createEvent(Player* player, Enemy* enemy) -> Event*
{
	Event* ev = new (std::nothrow)Event(player, enemy);
	
	if (!ev)
		logger->log("failed at creating event in Event::createEvent(Player* player, Enemy* enemy)",LL_WARNING);

	return ev;
}


auto	Event::eventReceiver() -> void
{
		const Uint8* state = SDL_GetKeyboardState(nullptr);
	
		float speedrun = player->getSpeedRun();
		float speed = player->getSpeed();
		float x = player->getPosition().val[0];
		float y = player->getPosition().val[1];
		float z = player->getPosition().val[2];	
		float rotx = player->getRotation().val[0];	
		float roty = player->getRotation().val[1];	
		float rotz = player->getRotation().val[2];	

		player->setEntityState(STATE_STANDING);
	
		player->entityIs();
		
		if (state[SDL_SCANCODE_S])
		{
			z += speed;
			player->setEntityState(STATE_WALKING);
			state[SDL_SCANCODE_R] ? z += speedrun : z += speed;
		}
	
		if (state[SDL_SCANCODE_W])
		{
			z -= speed;
			player->setEntityState(STATE_WALKING);
			state[SDL_SCANCODE_R] ? z -= speedrun : z -= speed;
		}
		
		if (state[SDL_SCANCODE_D])
		{
			x += speed;
			player->setEntityState(STATE_WALKING);
			state[SDL_SCANCODE_R] ? x += speedrun : x += speed;
		}

		if (state[SDL_SCANCODE_A])
		{
			x -= speed;
			player->setEntityState(STATE_WALKING);
			state[SDL_SCANCODE_R] ? x -= speedrun : x -= speed;
		}
		
		if (state[SDL_SCANCODE_R])
		{
			player->setEntityState(STATE_RUNNING);
		}
	
	
		if (state[SDL_SCANCODE_SPACE])
		{
			y += speed;
			player->setEntityState(STATE_JUMPING);
		}
		
		if (state[SDL_SCANCODE_C])
			y -= 1.f * speed;

		if (state[SDL_SCANCODE_Q])
			roty -= 5.f * speed;	

		if (state[SDL_SCANCODE_E])
			roty += 5.f * speed;	

	
		if (player->entityIs() == true)
		player->setPosition({x, y, z});
	
		std::cout << "speed : " << speed << std::endl;
		std::cout << player->getEntityState() << std::endl;
		std::cout << "MovementIs: " << player->entityIs() << std::endl;
		player->setRotation({rotx, roty, rotz});	
}

auto	enemyPatrol() -> void
{
	
}


}//namespace scene
}//namespace id 
