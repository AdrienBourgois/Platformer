#ifndef __EVENT_H_INCLUDED__
#define __EVENT_H_INCLUDED__


namespace id {
namespace scene {

class Player;
class Enemy;

class Event {

public :

	Event(Player* player);
	~Event();
	

	static auto createEvent(Player* player) -> Event*;

	auto eventReceiver() -> void;

private:

	Player* player;
	Enemy* enemy;

};


}//namespace scene
}//namespace id

#endif // __EVENT_H_INCLUDED__
