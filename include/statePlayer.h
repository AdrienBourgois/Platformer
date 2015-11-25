#ifndef __STATEPLAYER_H_INCLUDED__
#define __STATEPLAYER_H_INCLUDED__

namespace id {

namespace scene {


	class StatePlayer : public StateMachine {

	public:
	StatePlayer();
	~StatePlayer();
	
	auto	setEntityState(int state) -> int override {this->state = state;}
	auto	getEntityState() -> void override {return state;}

	private:
	int state;

	};

}//namespace scene 
}//namespace id 

#endif 
