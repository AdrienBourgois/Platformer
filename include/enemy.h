#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <vector>
#include "entity.h"

namespace id {
namespace scene {

class PathEnemy;

class Enemy 
: public Entity {

public:

	static auto createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path) -> Enemy*;
	virtual ~Enemy();
	Enemy(Enemy const&) = default;
	Enemy(Enemy&&) = delete;
	auto operator=(Enemy const&) -> Enemy& = default;
	auto operator=(Enemy&&) -> Enemy& = delete;

	auto getPath() const -> PathEnemy* { return pathEnemy; }
	
private:

	Enemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path);
	PathEnemy* pathEnemy;

};

}// namespace scene
}// namespace id

#endif // ENEMY_H_INCLUDED
