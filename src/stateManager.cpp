#include "stateManager.h"
#include "logger.h"
#include "elementId.h"

namespace id {
namespace scene {


StateManager::StateManager()
:state(STATE_STANDING)
{
	LOG(L_DEBUG, "Initializing StateManager...");

	LOG(L_DEBUG, "StateManager has been initialized.");
}

StateManager::~StateManager()
{
	LOG(L_DEBUG, "Deleting StateManager.");

	LOG(L_DEBUG, "StateManager has been deleted.");
}

auto StateManager::checkEntityState(int etat) -> bool
{
	if (state == etat)
		return true;
	else
		return false;
}

}//namespace scene
}//namespace id 
