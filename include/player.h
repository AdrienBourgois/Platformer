#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "entity.h"

namespace id {
namespace scene {

class Player : public Entity {

public:

	static auto createPlayer(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Player*;	

	~Player();

private:
	
	Player(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path);

};


}//namespace scene
}//namespace id


#endif // __PLAYER_H_INCLUDED__
