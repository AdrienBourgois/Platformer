#ifndef __EVENT_H_INCLUDED__
#define __EVENT_H_INCLUDED__


namespace id {

namespace scene {

class Player;

	class Event {
	
	public:
		~Event();

		static auto	createEvent() -> Event*;

		auto	setPlayer(Player* player) -> void {this->player = player;}
		auto	getPlayer() const -> Player* {return player;}	

		auto	updateEvent() -> void;		

	private:
	
	Event();

	Player* player;
//	float speed;
			
	};


}//namespace scene
}//namespace id 

#endif	
