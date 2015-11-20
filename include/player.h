#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "entity.h"

namespace id {

namespace scene {

	enum states {
	
		walk,
		jump,
		dead,
		stationary

	};

	class Player : public Entity {

	public: 
		~Player();
		static auto	createPlayer(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack) -> Player*;	

	private:
		
		Player(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack);

	};


}//namespace scene
}//namespace id 


#endif // __PLAYER_H_INCLUDED__
