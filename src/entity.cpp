#include <string>
#include "stateManager.h"
#include "elementId.h"
#include "entity.h"
#include "logger.h"

namespace id {
namespace scene {


Entity::Entity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)
:MeshSceneNode(scn, parent, name, shader, path), speed(0.f),speedrun(0.f), hp(0), life(0), attack(0)
{
	LOG(L_INFO,"Creating Entity ...");

	stateEntity = new StateManager();

	LOG(L_INFO,"Entity has been created.");
}

Entity::~Entity()
{
	LOG(L_INFO,"Deleting Entity ...");
		
	this->speed = 0;
	this->speedrun = 0;
	this->hp = 0;
	this->life = 0;
	this->attack = 0;
	delete stateEntity;
	this->stateEntity = nullptr;

	LOG(L_INFO,"Entity has been deleted.");
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
