#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "device.h"
#include "entity.h"

namespace id {
namespace scene {

class Player : public Entity {

public:

	static auto createPlayer(Device* dev, SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Player*;	

	virtual ~Player();

private:	
	Player(Device* dev, SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path);
	Device* dev;
};


}//namespace scene
}//namespace id


#endif 
