#include <iostream>
#include <string>

#include "elementId.h"
#include "enemy.h"
#include "player.h"
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


	inPursuit = false;
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
//	float speed = enemy->getSpeed();
	float x = enemy->getPosition().val[0];
	float y = enemy->getPosition().val[1];
	float z = enemy->getPosition().val[2];

	(void)deltaTime;

	enemy->entityIsMovement();
	enemy->entitySpeed();	
	enemy->setEntityState(STATE_WALKING);

	path.push_back({-10, 0, 0});
	path.push_back({10, 0, -10});
	path.push_back({-10, 0, 0});
/*
	if (inPursuit == false)
	{
		if (z <= path[index].val[2])
		{
			z +=  speed * deltaTime;
	
	
			if ((maths::Vector3){x, y, z} >= path[index])
			++index;
		}
	
		else
			z -= speed * deltaTime;
	
		if (x <= path[index].val[0])
		{
			x += speed * deltaTime;
			if ((maths::Vector3){x, y, z} >= path[index])
			++index;

		}

		else 
			x -= speed * deltaTime;
	}

*/		std::cout << "path : " << index << std::endl;

		std::cout << enemy->getPosition() << std::endl;

		enemy->setPosition({x, y, z});
}

auto PathEnemy::pursuit(Enemy* enemy, Player* player, float deltaTime) -> void
{


	float speed = enemy->getSpeed();
	float x = enemy->getPosition().val[0];
	float y = enemy->getPosition().val[1];
	float z = enemy->getPosition().val[2];
	
	float px = player->getPosition().val[0];
	float py = player->getPosition().val[1];
	float pz = player->getPosition().val[2];

/*	if (px >= x + 1.f || px >= x - 1.f)
	{
		chase.push_back({px, py, pz});	
				
		x += speed * deltaTime;
		z += speed * deltaTime;

		inPursuit = true;
	}*/
/*	else*/ if (px <= x - 1.f && py <= y + 1.f)
	{
		chase.push_back({px, py, pz});	
		x -= speed * deltaTime;
		z -= speed * deltaTime;	
	}

	else	
		inPursuit = false;
	enemy->setPosition({x, y, z});


	
}



}//namespace scene 
}//namespace id
