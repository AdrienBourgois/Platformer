#include <string>
#include <iostream>

#include "stateManager.h"
#include "elementId.h"
#include "entity.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();

}//namespace 

namespace id {
namespace scene {


Entity::Entity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)
:MeshSceneNode(scn, parent, name, shader, path), speed(0.f), state(STATE_STANDING), speedrun(0.f), hp(0), life(0), attack(0)
{
	logger->log("Creating Entity ...", LL_DEBUG);

	stateEntity = new StateManager();

	logger->log("Entity has been created.", LL_DEBUG);
}

Entity::~Entity()
{
	logger->log("Deleting Entity ...", LL_DEBUG);
		
	this->speed = 0;
	this->state = 0;
	this->speedrun = 0;
	this->hp = 0;
	this->life = 0;
	this->attack = 0;
	delete stateEntity;
	this->stateEntity = nullptr;

	logger->log("Entity has been deleted.", LL_DEBUG);
}

auto Entity::entitySpeed() -> void 
{
	if (STATE_WALKING)
		setSpeed(0.3f);

	if (STATE_RUNNING)
		setSpeedRun(1.f);

	else if (STATE_DEAD)
	{
		setSpeed(0.f);
		setSpeed(0.f);
	}
}

auto Entity::entityIsMovement() -> bool
{
	bool inMovement = false;

	if (STATE_WALKING)
		inMovement = true;

	else if (STATE_RUNNING)
		inMovement = true;

	else if (STATE_DEAD)
		inMovement = false;

	else
		inMovement = false;

	return inMovement;
}



}//namespace scene
}//namespace id 
