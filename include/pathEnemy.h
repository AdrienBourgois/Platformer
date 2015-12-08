#ifndef PATHENEMY_H_INCLUDED
#define PATHENEMY_H_INCLUDED

#include <vector>
#include "maths/vector.h"


namespace id {
namespace scene {

class PathEnemy {
	
public:
	PathEnemy();
	~PathEnemy();

	auto enemyPatrol(bool enemyReachPos) -> void;

private:
	std::vector<maths::Vector3> path;
	int index;

};

}//namespace scene
}//namespace id 

#endif
