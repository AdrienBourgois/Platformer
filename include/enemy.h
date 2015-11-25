#ifndef __ENEMY_H_INCLUDED__
#define __ENEMY_H_INCLUDED__

#include "entity.h"

namespace id {

namespace scene {

	class Enemy : public Entity {
	
	public:
		virtual ~Enemy();

		static auto	createEnemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack) -> Enemy*;

	private:

		Enemy(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack);

	};

}//namespace scene
}//namespace id

#endif // __ENEMY_H_INCLUDED__
