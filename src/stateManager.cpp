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
	logger->log("Initializing StateManager...", LL_DEBUG);

	logger->log("StateManager has been initialized.", LL_DEBUG);
}

StateManager::~StateManager()
{
	logger->log("Deleting StateManager.", LL_DEBUG);

	logger->log("StateManager has been deleted.", LL_DEBUG);
}

auto StateManager::entityIs() -> bool
{
	bool inMovement = false;	

	if (STATE_WALKING)
		inMovement = true;

	else if (STATE_RUNNING)
		inMovement = true;

	else
		inMovement = false;

	return inMovement;
}

}//namespace scene
}//namespace id 
