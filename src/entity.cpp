#include <string>
#include <iostream>

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

	logger->log("Entity has been created.", LL_DEBUG);
}

Entity::~Entity()
{
	logger->log("Deleting Entity ...", LL_DEBUG);


	logger->log("Entity has been deleted.", LL_DEBUG);
}

auto Entity::entitySpeedIs() -> void 
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


}//namespace scene
}//namespace id 
