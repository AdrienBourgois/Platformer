#include "stateManager.h"
#include "txtLogger.h"
#include "elementId.h"

namespace {

	id::TXTLogger* logger = id::TXTLogger::getInstance();
}


namespace id {
namespace scene {

StateManager::StateManager()
{
	logger->log("Creating StateManager ...", LL_DEBUG);


	logger->log("StateManager has been created.", LL_INFO);
}

StateManager::~StateManager()
{
	logger->log("Deleting StateManager ...", LL_DEBUG);

	logger->log("StateManager has been deleted.", LL_INFO);
}


/*auto	StateManager::entityIs() -> bool
{
	bool inMovement = false;

	if (getEntityState() == STATE_WALKING)
		inMovement = true;

	if (getEntityState() == STATE_RUNNING)
		inMovement = true;

	if (getEntityState() == STATE_STANDING)
		inMovement = false;

	return inMovement;

}
*/
}//namespace scene
}//namespace id 
