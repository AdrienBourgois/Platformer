#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include <vector>
#include "entity.h"

namespace id {
namespace scene {

class Enemy : public Entity {

public:

	static auto createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Enemy*;
	~Enemy();

	auto enemyPatrol() -> void;

private:

	Enemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path);
	std::vector<maths::Vector3> pos;
	

};

}//namespace scene
}//namespace id

#endif // __ENEMY_H_INCLUDED__
