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


}//namespace scene
}//namespace id 
