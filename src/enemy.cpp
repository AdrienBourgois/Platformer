#include <string>
#include <iostream>
#include <vector>


#include "enemy.h"
#include "txtLogger.h"


namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();

}


namespace id {

namespace scene {


auto	Enemy::createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack) -> Enemy*
{
//	SDL_assert(scn && parent);

	Enemy* enemy = new (std::nothrow)Enemy(scn, parent, name, shader, path, eLife, eHp, eAttack);

	if (!enemy)
		logger->log("failed at creating enemy in Enemy::createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack", LL_WARNING);

	return enemy;
}

Enemy::Enemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack)
:Entity(scn, parent, name, shader, path, eLife, eHp, eAttack)
{
	logger->log("Creating Enemy...", LL_DEBUG);

	eLife = enLife;
	eHp = enHp;
	eAttack = enAttack;

	
	logger->log("Enemy has been created.", LL_INFO);
}

Enemy::~Enemy()
{
	
	logger->log("Deleting Enemy...", LL_DEBUG);

	logger->log("Enemy has been deleted.", LL_INFO);
}
}//namespace scene
}//namespace id
