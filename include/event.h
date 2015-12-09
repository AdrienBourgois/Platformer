#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED


namespace id {
namespace scene {

class Player;
class Enemy;

class Event {

public :

	Event(Player* player);
	~Event();
	

	static auto createEvent(Player* player) -> Event*;

	auto eventReceiver(float deltaTime) -> void;



private:

	Player* player;
	Enemy* enemy;

};


}//namespace scene
}//namespace id

#endif 
