#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED
#include "elementId.h"

namespace id {
namespace scene {

class StateManager {

public:

	StateManager();
	virtual ~StateManager();

	virtual auto setEntityState(int state) -> void {this->state = state;}
	virtual auto getEntityState() -> int {return state;}
	virtual auto checkEntityState(int etat) -> bool;

private:
	int state;

};

}//namespace scene
}//namespace id 




#endif // STATEMANAGER_H_INCLUDED
