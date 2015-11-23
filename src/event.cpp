#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <SDL2/SDL.h>

#include "sceneNode.h"
#include "event.h"
#include "player.h"
#include "txtLogger.h"
#include "entity.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}


namespace id {

namespace scene {


Event::Event()
{
	logger->log("Creating Event...", LL_DEBUG);
	

	logger->log("Event has been created.", LL_INFO);	
}


Event::~Event()
{
	logger->log("Deleting Event...", LL_DEBUG);

	logger->log("Event has been deleted.", LL_INFO);

}

auto	Event::createEvent() -> Event*
{
	Event* ev = new (std::nothrow)Event();
	
	if (!ev)
		logger->log("failed at creating event in Event::createEvent()",LL_WARNING);

	return ev;
}


auto	Event::updateEvent() -> void
{
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		
	//	float speed = 2.f;
		
		if (state[SDL_SCANCODE_W])
			
}

}//namespace scene
}//namespace id 
