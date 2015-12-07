#ifndef __EVENT_H_INCLUDED__
#define __EVENT_H_INCLUDED__


namespace id {
namespace scene {

class Player;
class Enemy;

class Event {

public :

	Event(Player* player, Enemy* enemy);
	~Event();
	

	static auto createEvent(Player* player) -> Event*;

	auto eventReceiver(float deltaTime) -> void;


//	auto setPlayer(Player* player) -> void {this->player = player;}
//	auto getPlayer() const -> Player* {return player;}


private:

	Player* player;
	Enemy* enemy;

};


}//namespace scene
}//namespace id

#endif // __EVENT_H_INCLUDED__
