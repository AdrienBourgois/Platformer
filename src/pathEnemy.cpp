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
	speedX = 0;
	speedZ = 0;
	
	logger->log("PathEnemy hsa been initialized.", LL_DEBUG);
}

PathEnemy::~PathEnemy()
{
	logger->log("Deleting PathEnemy...", LL_DEBUG);

	logger->log("PathEnemy has been deleting.", LL_DEBUG);
}


auto PathEnemy::enemyPatrol(Enemy* enemy, float deltaTime) -> void
{
	//float speed = enemy->getSpeed();
	float x = enemy->getPosition().val[0];
	float y = enemy->getPosition().val[1];
	float z = enemy->getPosition().val[2];


	enemy->entityIsMovement();
	enemy->entitySpeed();	
	enemy->setEntityState(STATE_WALKING);

	path.push_back({0, 0, 0});
	path.push_back({10, 0, 0});
	path.push_back({10, 0, -10});
	path.push_back({-10, 0, 0});

//	if (inPursuit == false)
//	{
		float distanceX;
		float distanceZ;
		(path[index].val[0] < 0) ? distanceX = -path[index].val[0] + x: distanceX = path[index].val[0] - x;
		(path[index].val[2] < 0) ? distanceZ = -path[index].val[2] + z: distanceZ = path[index].val[2] - z;

		if (distanceX <= 0 && distanceZ <= 0)
		{
			++index;
			(path[index].val[0] < 0) ? distanceX = -path[index].val[0] + x: distanceX = path[index].val[0] - x;
			(path[index].val[2] < 0) ? distanceZ = -path[index].val[2] + z: distanceZ = path[index].val[2] - z;
			speedX = distanceX/20.f;
			speedZ = distanceZ/20.f;
		}
		
		if (distanceZ > 0)
		{
			if (z <= path[index].val[2])
				z +=  speedZ * deltaTime;
			else
				z -= speedZ * deltaTime;
		}

		if (distanceX > 0)
		{
			if (x <= path[index].val[0])
				x += speedX * deltaTime;
			else 
				x -= speedX * deltaTime;
		}
//	}
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

	if (px >= x + 1.f || px >= x - 1.f)
	{
		chase.push_back({px, py, pz});	
				
		x += speed * deltaTime;
		z += speed * deltaTime;

		inPursuit = true;
	}
	else if (px <= x - 1.f && py <= y + 1.f)
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
