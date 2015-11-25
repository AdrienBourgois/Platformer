#ifndef __STATEMACHINE_H_INCLUDED__
#define __STATEMACHINE_H_INCLUDED__
#include "elementId.h"


namespace id {
namespace scene {

	class StateMachine {

	public:
		StateMachine();
		virtual ~StateMachine();
		
		virtual auto	setEntityState(int state) -> void {this->state = state;}
		virtual auto	getEntityState() -> int {return state;}		

	private:

	int state;

	};


}//namespace scene
}//namespace id 


#endif
