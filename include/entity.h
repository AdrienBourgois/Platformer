#ifndef __ENTITY_H_INCLUDED__
#define __ENTIYT_H_INCLUDED__

namespace id {

class Entity {

	public:
		Entity();
		~Entity() = default;

		auto	setLife(int l) -> void {life = l;} 
		auto	setHp(int h) -> void {hp = h;}
		auto	setAttack(int a) -> void {attack = a;}

		auto	getLife() -> int {return life;}
		auto	getHp() -> int {return hp;}
		auto	getAttack() -> int {return attack;}

	private:

	int life;
	int hp;
	int attack;

}
}//namespace id

#endif // __ENTITY_H_INCLUDED__
