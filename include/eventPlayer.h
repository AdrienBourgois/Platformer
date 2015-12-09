#ifndef EVENT_PLAYER_H_INCLUDED
#define EVENT_PLAYER_H_INCLUDED

#include <SDL2/SDL.h>
#include <map>
#include <string>

#include "eventReceiver.h"
#include "device.h"
#include "player.h"

namespace id {
namespace event {

class EventPlayer : public EventReceiver
{
public:
	EventPlayer(Device* dev, std::string name, scene::Player* player);
	~EventPlayer();

	virtual auto eventListener() -> void;
	auto loadKeys() -> void;

private:
	scene::Player* player;
	std::map<std::string, SDL_Scancode> scancodeKeys;
};

} // end namespace event

} // end namespace id

#endif // EVENT_PLAYER_H_INCLUDED
