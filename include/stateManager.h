#ifndef __STATEMANAGER_H_INCLUDED__
#define __STATEMANAGER_H_INCLUDED__
#include "elementId.h"

namespace id {
namespace scene {

class StateManager {

public:

	StateManager();
	virtual ~StateManager();

	virtual auto setEntityState(int state) -> void {this->state = state;}
	virtual auto getEntityState() -> int {return state;}
	
	virtual auto entityIs() -> bool;

private:
	int state;

};

}//namespace scene
}//namespace id 




#endif // __STATEMANAGER_H_INCLUDED__
