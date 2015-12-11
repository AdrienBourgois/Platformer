#ifndef PATHENEMY_H_INCLUDED
#define PATHENEMY_H_INCLUDED

#include <vector>
#include "maths/vector.h"



namespace id {
namespace scene {

class Enemy;
class Player;

class PathEnemy {
	
public:
	PathEnemy(maths::Vector3 pos);
	~PathEnemy();

	auto enemyPatrol(Enemy* enemy, float deltaTime) -> void;
	auto pursuit(Enemy* enemy, Player* player, float deltaTime) -> void;
	auto addPath(maths::Vector3 pathPoint) -> void;

private:
	std::vector<maths::Vector3> path;
	int index;
	std::vector<maths::Vector3> chase;
	bool inPursuit;
	float speedX;
	float speedZ;

};

}//namespace scene
}//namespace id 

#endif
