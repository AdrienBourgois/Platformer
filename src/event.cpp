#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <cmath>

#include "sceneNode.h"
#include "sceneManager.h"
#include "event.h"
#include "player.h"
#include "txtLogger.h"
#include "entity.h"
#include "maths/polyhedronCollider.h"

#include <iostream>
namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}


namespace id {

namespace scene {


Event::Event(Player* player)
:player(player)
{
	logger->log("Creating Event...", LL_DEBUG);
	

	logger->log("Event has been created.", LL_INFO);	
}


Event::~Event()
{
	logger->log("Deleting Event...", LL_DEBUG);

	logger->log("Event has been deleted.", LL_INFO);

}

auto	Event::createEvent(Player* player) -> Event*
{
	Event* ev = new (std::nothrow)Event(player);
	
	if (!ev)
		logger->log("failed at creating event in Event::createEvent()",LL_WARNING);

	return ev;
}


auto	Event::updateEvent() -> void
{
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		
		float speed = 0.3f;
		float x = player->getPosition().val[0];
		float y = player->getPosition().val[1];
		float z = player->getPosition().val[2];	
		float rotx = player->getRotation().val[0];	
		float roty = player->getRotation().val[1];	
		float rotz = player->getRotation().val[2];	

		if (state[SDL_SCANCODE_S])
		{
			z += 1.f * speed;
		}
	
		if (state[SDL_SCANCODE_W])
		{
			z -= 1.f * speed;
		}
	
		if (state[SDL_SCANCODE_E])
		{
			if (state[SDL_SCANCODE_W])
				x += 1.f * speed * 1 /sqrt(2);
			else
				x += 1.f * speed;
		}

		if (state[SDL_SCANCODE_Q])
		{
			x -= 1.f * speed;
		}

		if (state[SDL_SCANCODE_SPACE])
		{
			y += 1.f * speed;
		}
		
		if (state[SDL_SCANCODE_C])
		{
			y -= 1.f * speed;
		}

		if (state[SDL_SCANCODE_A])
		{
			roty += 5.f * speed;	
		}	

		if (state[SDL_SCANCODE_D])
		{
			roty -= 5.f * speed;	
		}	

		player->setPosition({x, y, z});
		player->setRotation({rotx, roty, rotz});

		for (auto&& node : player->getScene()->getRootNode()->getChildrens())	
			if (player->getPolyhedronCollider()->collide(node->getPolyhedronCollider()) && player != node)
			{
				std::cout << "collision" << std::endl;
			}

}

}//namespace scene
}//namespace id 
