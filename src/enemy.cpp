#include <iostream>
#include <string>

#include "enemy.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger * logger = id::TXTLogger::getInstance();

}//namespace 

namespace id {
namespace scene {

Enemy::Enemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)
:Entity(scn, parent, name, shader, path)
{
	logger->log("Creating Enemy...", LL_DEBUG);

	setHp(1);
	setLife(1);
	setAttack(1);

	logger->log("Enemy has been created.", LL_DEBUG);	
}

Enemy::~Enemy()
{
	logger->log("Deleting Enemy...", LL_DEBUG);
	
	logger->log("Enemy has been Enemy", LL_DEBUG);
}

auto Enemy::createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Enemy*
{
	Enemy* enemy = new (std::nothrow)Enemy(scn, parent, name, shader, path);

	if (!enemy)
		logger->log("failed at created enemy in Enemy::createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)", LL_WARNING);

	return enemy;
}


auto Enemy::enemyPatrol() -> void
{
	
	this->pos[1] = {0.f, 2.f, 0.f};

}



}//namespace scene
}//namespace id
