#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include <SDL2/SDL.h>
#include <string>
#include <map>

namespace id {
namespace scene {

class Player;
class Enemy;

class Event
{
public :
	Event(Player* player);
	~Event();
	
	static auto createEvent(Player* player) -> Event*;

	auto eventReceiver(float deltaTime) -> void;
	auto loadKeys() -> void;

private:
	Player* player;
	Enemy* enemy;
	std::map<std::string, SDL_Scancode> scancodeKeys;
};


} // end namespace scene
} // end namespace id

#endif // EVENT_H_INCLUDED
