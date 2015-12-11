#include <iostream>
#include <string>

#include "enemy.h"
#include "pathEnemy.h"
#include "logger.h"

namespace id {
namespace scene {

Enemy::Enemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)
:Entity(scn, parent, name, shader, path)
{
	LOG(L_INFO,"Creating Enemy...");


	pathEnemy = new PathEnemy(this->getPosition());

	setHp(1);
	setLife(1);
	setAttack(1);

	LOG(L_INFO,"Enemy has been created.");	
}

Enemy::~Enemy()
{
	LOG(L_INFO,"Deleting Enemy...");
	
	LOG(L_INFO,"Enemy has been Enemy.");
}

auto Enemy::createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Enemy*
{
	Enemy* enemy = new (std::nothrow)Enemy(scn, parent, name, shader, path);

	if (!enemy)
		LOG(L_WARNING,"failed at created enemy in Enemy::createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path)");

	return enemy;
}


}//namespace scene
}//namespace id
