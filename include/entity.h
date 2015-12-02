#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "stateManager.h"
#include "meshSceneNode.h"

namespace id {
namespace scene {

class Entity : public MeshSceneNode, public StateManager {

public:

	~Entity();


	virtual auto setEntityState(int state) -> void override {this->state = state;}
	virtual auto getEntityState() -> int override {return state;}


	virtual auto setSpeed(float speed) -> void {this->speed = speed;}
	virtual auto getSpeed() const -> float {return speed;}

	
	virtual auto setSpeedRun(float speedrun) -> void {this->speedrun = speedrun;}
	virtual auto getSpeedRun() const -> float {return speedrun;}

	
	virtual auto entitySpeedIs() -> void;

protected:

	Entity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path);

	float speed;
	int state;
	float speedrun;

};


}//namespace scene
}//namespace id 



#endif // __ENTITY_H_INCLUDED__
