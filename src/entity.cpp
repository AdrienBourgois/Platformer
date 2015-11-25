#include <string>
#include <iostream>
#include <vector>

#include "mesh.h"
#include "maths/utility.h"
#include "maths/vector.h"
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
: MeshSceneNode(scn, parent, name, shader, "", maths::Shape::cube), life(eLife), hp(eHp), attack(eAttack)
{
	(void)path;
	logger->log("Creating Entity...", LL_DEBUG);
		
		life = 0;
	hp = 0;
	attack = 0;

	logger->log("Entity has been created.", LL_INFO);
}

Entity::~Entity()
{
	logger->log("Entity deleting ...", LL_DEBUG);

	logger->log("Entity has been deleted.", LL_INFO);
}





}//namespace scene 
}//namespace id
