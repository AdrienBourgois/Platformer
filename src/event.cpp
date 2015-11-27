#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>

#include "elementId.h"
#include "sceneNode.h"
#include "event.h"
#include "player.h"
#include "txtLogger.h"
#include "entity.h"
#include "maths/matrix.h"
#include <cmath>

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}


namespace id {

namespace scene {


Event::Event(Player* player, Enemy* enemy)
:player(player), enemy(enemy)
{
	logger->log("Creating Event...", LL_DEBUG);
	
	player->setSpeed(1.f);	

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
	
		bool run = false;	
		float speed = player->getSpeed();
		float x = player->getPosition().val[0];
		float y = player->getPosition().val[1];
		float z = player->getPosition().val[2];	
		float rotx = player->getRotation().val[0];	
		float roty = player->getRotation().val[1];	
		float rotz = player->getRotation().val[2];	

		player->setEntityState(STATE_STANDING);

		
		
		if (state[SDL_SCANCODE_W])
		{	
			z += 1.f * speed;
			player->setEntityState(STATE_WALKING);
		}
	
		if (state[SDL_SCANCODE_S])
		{
			z -= 1.f * speed;
			player->setEntityState(STATE_WALKING);
		}
		
		if (state[SDL_SCANCODE_D])
		{
			x += 1.f * speed;
			player->setEntityState(STATE_WALKING);
		}

		if (state[SDL_SCANCODE_A])
		{
			x -= 1.f * speed;
			player->setEntityState(STATE_WALKING);
		}
		if (state[SDL_SCANCODE_R] && run == false)
		{
			player->setSpeed(2.f);	
			run = true;
			player->setEntityState(STATE_RUNNING);
		}
		if (state[SDL_SCANCODE_SPACE])
		{
			y += 1.f * speed;
			player->setEntityState(STATE_JUMPING);
		}
		
		if (state[SDL_SCANCODE_C])
			y -= 1.f * speed;

		if (state[SDL_SCANCODE_Q])
			roty -= 5.f * speed;	

		if (state[SDL_SCANCODE_E])
			roty += 5.f * speed;	

		

		std::cout << player->getEntityState() << std::endl;
		player->setPosition({x, y, z});
		player->setRotation({rotx, roty, rotz});	
}

auto	enemyPatrol() -> void
{
	
}


}//namespace scene
}//namespace id 
