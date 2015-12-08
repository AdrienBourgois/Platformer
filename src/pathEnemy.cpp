#include <iostream>
#include <string>

#include "enemy.h"
#include "pathEnemy.h"
#include "txtLogger.h"

namespace {

	id::TXTLogger * logger = id::TXTLogger::getInstance();
}//namespace 

namespace id {
namespace scene {


PathEnemy::PathEnemy()
{
	logger->log("Initializing PathEnemy...", LL_DEBUG);

	logger->log("PathEnemy hsa been initialized.", LL_DEBUG);
}

PathEnemy::~PathEnemy()
{
	logger->log("Deleting PathEnemy...", LL_DEBUG);

	logger->log("PathEnemy has been deleting.", LL_DEBUG);
}


auto PathEnemy::enemyPatrol(Enemy* enemy) -> void
{
	float x = enemy->getPosition().val[0];
	float y = enemy->getPosition().val[1];
	float z = enemy->getPosition().val[2];
	
	path.push_back({0, 0, 0});
	path.push_back({0, 2, 0});

	y += 0.5f;

	if ((maths::Vector3){x, y, z} == path[1])
	    std::cout << "Point atteint ! Hourra joie bonheur !" << std::endl;
	

	enemy->setPosition({x, y, z});
}

}//namespace scene 
}//namespace id
