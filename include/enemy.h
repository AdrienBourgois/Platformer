#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <vector>
#include "entity.h"

namespace id {
namespace scene {

class PathEnemy;

class Enemy : public Entity {

public:

	static auto createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Enemy*;
	~Enemy();

	auto enemyPatrol(bool enemyReachPos) -> void;

private:

	Enemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path);
	std::vector<maths::Vector3> pos;
	PathEnemy* path;	

};

}//namespace scene
}//namespace id

#endif 
