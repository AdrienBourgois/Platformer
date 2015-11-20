#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "meshSceneNode.h"



namespace id {

namespace scene {

	class Entity : public MeshSceneNode {

	public:
		virtual ~Entity();

		static auto	createEntity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack) -> Entity*;

		auto	setLife(int l) -> void {life = l;} 
		auto	setHp(int h) -> void {hp = h;}
		auto	setAttack(int a) -> void {attack = a;}

		auto	getLife() const -> int {return this->life;}
		auto	getHp() const -> int {return this->hp;}
		auto	getAttack() const -> int {return this->attack;}

	protected:

		Entity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack);
	int life;
	int hp;
	int attack;

	};
}//namespace scene 
}//namespace id

#endif // __ENTITY_H_INCLUDED__
