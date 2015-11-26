#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED


namespace id {
namespace scene {

class Player;

class Event
{
public:
	~Event();

	static auto	createEvent(Player* player) -> Event*;

	auto	setPlayer(Player* player) -> void {this->player = player;}
	auto	getPlayer() const -> Player* {return player;}	

	auto	updateEvent() -> void;		

private:	
	Event(Player* player);

	Player* player;
	std::vector<Player*> facing;	
};

}//namespace scene
}//namespace id 

#endif // EVENT_H_INCLUDED	
