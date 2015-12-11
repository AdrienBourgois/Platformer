#include <string>

#include "elementId.h"
#include "enemy.h"
#include "player.h"
#include "pathEnemy.h"
#include "logger.h"
#include "stateManager.h"

namespace id {
namespace scene {


PathEnemy::PathEnemy(maths::Vector3 pos)
{
	LOG(L_DEBUG, "Initializing PathEnemy...");


	index = 0;
	speedX = 0;
	speedZ = 0;
	path.push_back(pos);
	
	LOG(L_DEBUG, "PathEnemy hsa been initialized.");
}

PathEnemy::~PathEnemy()
{
	LOG(L_DEBUG, "Deleting PathEnemy...");

	LOG(L_DEBUG, "PathEnemy has been deleting.");
}


auto PathEnemy::enemyPatrol(Enemy* enemy, float deltaTime) -> void
{
	float x = enemy->getPosition().val[0];
	float y = enemy->getPosition().val[1];
	float z = enemy->getPosition().val[2];

	enemy->entityIsMovement();
	enemy->entitySpeed();	
	enemy->getEntityState()->setEntityState(STATE_WALKING);

	float distanceX;
	float distanceZ;
	(path[index].val[0] < 0) ? distanceX = -path[index].val[0] + x: distanceX = path[index].val[0] - x;
	(path[index].val[2] < 0) ? distanceZ = -path[index].val[2] + z: distanceZ = path[index].val[2] - z;

	if (distanceX <= 0 && distanceZ <= 0)
	{
		if (path.begin() + index == path.end() - 1)
			index = 0;
		else
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
	enemy->setPosition({x, y, z});
}
auto PathEnemy::addPath(maths::Vector3 pathPoint) -> void
{
	path.push_back(pathPoint);
}

}//namespace scene 
}//namespace id
