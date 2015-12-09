#include <iostream>
#include <string>

#include "elementId.h"
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

	index = 0;
	
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

	index = 1;

	enemy->entityIsMovement();
	enemy->entitySpeed();	
	enemy->setEntityState(STATE_WALKING);

	path.push_back({0, 0, 0});
	path.push_back({0, 0, -10});
	path.push_back({10, 0, -10});
	path.push_back({10, 0, 20});


	if ((maths::Vector3){x, y, z} >= path[1])
	{
		z -=  speed * deltaTime;
	}

	else if ((maths::Vector3){x, y, z} <= path[2])
	{
		x += speed * deltaTime;
	}	

	else if ((maths::Vector3){x, y, z} <= path[3])
		z -=  speed * deltaTime;
	

		enemy->setPosition({x, y, z});
}

}//namespace scene 
}//namespace id
