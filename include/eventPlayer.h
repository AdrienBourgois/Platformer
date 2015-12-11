#ifndef EVENT_PLAYER_H_INCLUDED
#define EVENT_PLAYER_H_INCLUDED

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "eventReceiver.h"

namespace id {

class Device;

namespace scene {
	class Player;
} // namespace scene

namespace event {

class EventPlayer 
: public EventReceiver
{
public:
	EventPlayer(Device* dev, std::string name, scene::Player* player);
	virtual ~EventPlayer();

	virtual auto eventListener() -> void;
	auto loadKeys() -> void;

	auto setPlayer(scene::Player* player) -> void 	{ this->player = player; }
	auto getPlayer() -> scene::Player* 				{ return player; }
	auto deletePlayer() -> void;

private:
	scene::Player* player;
	std::map<std::string, SDL_Scancode> scancodeKeys;
};

} // namespace event
} // namespace id

#endif // EVENT_PLAYER_H_INCLUDED
