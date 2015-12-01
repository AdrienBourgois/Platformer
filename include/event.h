#ifndef __EVENT_H_INCLUDED__
#define __EVENT_H_INCLUDED__


namespace id {

	class Device;

namespace scene {

class Player;
class Enemy;
class StatePlayer;


	class Event {
	
	public:
		~Event();

		static auto	createEvent(Player* player, Enemy* enemy) -> Event*;
/*
		auto	setPlayer(Player* player) -> void {this->player = player;}
		auto	getPlayer() const -> Player* {return player;}	

		auto	setEnemy(Enemy* enemy) -> void {this->enemy = enemy;}
		auto	getEnemy() const -> Enemy* {return enemy;}
*/
		auto	getDevice() const -> Device* {return dev;}


		auto	eventReceiver() -> void;		
		auto	enemyPatrol() -> void;

	private:
	Player* player;	
	Enemy* enemy;
	
	Device* dev;	
	
	Event(Player* player, Enemy* enemy);
	

	};


}//namespace scene
}//namespace id 

#endif	
