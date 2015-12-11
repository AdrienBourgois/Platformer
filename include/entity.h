#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "meshSceneNode.h"

namespace id {
namespace scene {

class StateManager;

class Entity 
: public MeshSceneNode {

public:

	virtual ~Entity();
	Entity(Entity const&) = delete;
	Entity(Entity&&) = delete;
	auto operator=(Entity const&) -> Entity& = delete;
	auto operator=(Entity&&) -> Entity& = delete;

	virtual auto setSpeed(float speed) -> void 			{ this->speed = speed;		 }
	virtual auto getSpeed() const -> float 				{ return speed;				 }
	
	virtual auto setSpeedRun(float speedrun) -> void 	{ this->speedrun = speedrun; }
	virtual auto getSpeedRun() const -> float 			{ return speedrun;			 }

	virtual auto setHp(unsigned int hp) -> void 		{ this->hp = hp;			 }
	virtual auto getHp() const -> unsigned int 			{ return hp;				 }

	virtual auto setLife(unsigned int life) -> void 	{ this->life = life;		 }
	virtual auto getLife() const -> unsigned int 		{ return life;				 }

	virtual auto setAttack(unsigned int attack) -> void { this->attack = attack;	 }
	virtual auto getAttack() const -> unsigned int 		{ return attack; 			 }

	virtual auto getEntityState() -> StateManager* 		{ return stateEntity; 		 }

	virtual auto entitySpeed() -> void; 
	virtual auto entityIsMovement() -> bool;	
	

protected:

	Entity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path);

	float 		 speed;
	float 		 speedrun;
	unsigned int hp;
	unsigned int life;
	unsigned int attack;

	StateManager* stateEntity;

};


}// namespace scene
}// namespace id 



#endif // ENTITY_H_INCLUDED
