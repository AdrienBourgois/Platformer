#ifndef __ENTITY_H_INCLUDED__
#define __ENTITY_H_INCLUDED__

#include "stateManager.h"

#include "meshSceneNode.h"



namespace id {

namespace scene {

	class Entity : public MeshSceneNode, public StateManager {

	public:
		virtual ~Entity();

		static auto	createEntity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack) -> Entity*;

		virtual auto	setLife(int l) -> void {life = l;} 
		virtual auto	setHp(int h) -> void {hp = h;}
		virtual auto	setAttack(int a) -> void {attack = a;}

		virtual auto	getLife() const -> int {return life;}
		virtual auto	getHp() const -> int {return hp;}
		virtual auto	getAttack() const -> int {return attack;}
	
		virtual auto	setEntityState(int state) -> void override {this->state = state;}
		virtual auto	getEntityState() -> int override {return state;}

//		virtual	auto	

	protected:


		Entity(SceneManager* scn, SceneNode* parent, std::string const& name, std::string const& shader, std::string const& path, int eLife, int eHp, int eAttack);

	unsigned int life;
	unsigned int hp;
	unsigned int attack;
	int state;

	};
}//namespace scene 
}//namespace id

#endif // __ENTITY_H_INCLUDED__
