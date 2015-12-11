#include <iostream>
#include <string>

#include "elementId.h"
#include "enemy.h"
#include "pathEnemy.h"
#include "txtLogger.h"
#include "stateManager.h"
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


auto PathEnemy::enemyPatrol(Enemy* enemy, float deltaTime) -> void
{
	float speed = enemy->getSpeed();
	float x = enemy->getPosition().val[0];
	float y = enemy->getPosition().val[1];
	float z = enemy->getPosition().val[2];


	enemy->entityIsMovement();
	enemy->entitySpeed();	
	enemy->getEntityState()->setEntityState(STATE_WALKING);

	path.push_back({0, 0, 0});
	path.push_back({0, 0, -50});


	while ((maths::Vector3){x, y, z} != path[1])	
	z -=  speed * deltaTime;

	if ((maths::Vector3){x, y, z} <= path[1])
	{
		speed = 0.f;
		std::cout << "Point atteint ! Hourra joie bonheur !" << std::endl;
		enemy->getEntityState()->setEntityState(STATE_STANDING);
	}

	enemy->setPosition({x, y, z});
}

}//namespace scene 
}//namespace id
