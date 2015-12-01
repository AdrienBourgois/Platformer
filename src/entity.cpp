#include <string>
#include <iostream>
#include <vector>

#include "elementId.h"
#include "entity.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();

}

namespace id {
namespace scene {


 auto     Entity::createEntity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack) -> Entity*
{
//	SDL_assert(scn && parent);

	Entity* entity = new (std::nothrow)Entity(scn, parent, name, shader, path, eLife, eHp, eAttack);
	
	if (!entity)
		logger->log("failed at created entity in Entity::createEntity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack)", LL_WARNING);

	return entity;
}


Entity::Entity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack)
:MeshSceneNode(scn, parent, name, shader, path), life(eLife), hp(eHp), attack(eAttack), state(STATE_STANDING)
{
	logger->log("Creating Entity...", LL_DEBUG);


	logger->log("Entity has been created.", LL_INFO);
}

Entity::~Entity()
{
	logger->log("Entity deleting ...", LL_DEBUG);

	logger->log("Entity has been deleted.", LL_INFO);
}

auto	Entity::entityIs() -> void 
{
		float speed = 0.f;


		if (getEntityState() == STATE_WALKING)
		{
			speed = 1.f;
			setSpeed(speed);
		}		

		else if (getEntityState() == STATE_RUNNING)
		{
			speed = 2.f;
			setSpeedRun(speed);
		}

		
}



}//namespace scene 
}//namespace id
